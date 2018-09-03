# Name: Jonathan Perry
# Date: 8/12/2018
# Class: CS 372
# Project: Project 2
import select, socket, sys, os
import signal
import time
from os import path
from functools import partial
from struct import *
PORT_MIN = 1024
PORT_MAX = 65535
SERVER_LIST = ("flip1", "flip2", "flip3", "localhost")

def main():
    # This function handles all SIGINT (ctrl+c) action and exits the program.
    def sigint_handler(myConn, signum, frame):
        myConn.close()
        sys.exit(1)
    # 3. ftpclient starts on Host B, and validate any pertinent command-line parameters.
    #  <SERVER_HOST>. <SERVER_PORT>, <COMMAND>, <FILENAME>, <DATA_PORT>, etc.
    def checkArgs():
        global SERVER_HOST, SERVER_PORT, COMMAND, FILE_NAME, DATA_PORT
        if len(sys.argv[1:]) not in (5, 6):
            print('Only 5-6 arguments needed. Expected Input: <SERVER_HOST> <SERVER_PORT> <COMMAND> <FILENAME> <DATA_PORT> Please try again. ')
            sys.exit(1)
        else:
            if sys.argv[1] not in SERVER_LIST:
                print("ERROR: Ftpclient can only connect to flip1, flip2, flip3 servers. Exiting!")
                sys.exit(1)
            elif int(sys.argv[2]) not in range(PORT_MIN, PORT_MAX):
                print("ERROR: Ftpclient can only connect on ports [", PORT_MIN, " - ", PORT_MAX, "] for the SERVER_PORT")
                print("User has set SERVER_PORT to: ", sys.argv[2])
                sys.exit(1)
            elif sys.argv[3] not in ("-l", "-g"):
                print("ERROR: -l or -g command expected, but not entered")
                sys.exit(1)
            elif int(sys.argv[5]) not in range(PORT_MIN, PORT_MAX):
                print("ERROR: Ftpclient can only connect on ports [", PORT_MIN, " - ", PORT_MAX, "] for the DATA_PORT")
                print("User has set DATA_PORT to: ", sys.argv[5])
                sys.exit(1)
            elif int(sys.argv[2]) == int(sys.argv[5]):
                print("ERROR: SERVER_PORT and DATA_PORT cannot be the same!")
                sys.exit(1)
            else: # arguments have been sent correctly, assign global variables
                SERVER_HOST = sys.argv[1]
                SERVER_PORT = int(sys.argv[2])
                COMMAND = sys.argv[3]
                FILE_NAME = sys.argv[4]
                DATA_PORT = int(sys.argv[5])
                if COMMAND == "-g":  # if the user has sent the -g command, a seperate connection (connectionP) will be needed to transfer files
                    return True;  # true - we need a seperate connection to transfer files
                else:
                    return False; # false - we only need 1 connection to receive the names of each file in the directory of ftpserver.c
    # checks args and returns true/false if the user has entered '-g', which means that a seperate connection with the server needs to be established to transfer files
    G_COMMAND = checkArgs() 
    try: # 7.2a ftpserver initiates a TCP data connection with ftpclient on <DATA_PORT> (call this connection Q)
        # ftpclient in this case will act as the server, and ftpserver will act as the client during this file transfer process
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create TCP welcoming socket
        serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        serverSocket.bind(("", DATA_PORT)) # bind our port number to our socket
        print("ConnectionQ - Socket successfully created")
    except socket.error as err:
        print("ConnectionQ - Socket created failed with error: ", err)
        sys.exit()
    try:
        # 4. ftpserver and ftpclient establish a TCP controll connection on <SERVER_PORT>. (for the remainder of this description, call this connection P)
        connectionP = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create TCP welcoming socket
        print("ConnectionP - Socket successfully created")
    except socket.error as err:
        print("ConnectionP - Socket created failed with error ", err)
        sys.exit()
    signal.signal(signal.SIGINT, partial(sigint_handler, connectionP)) # Set up our signal handler to handle ctrl+c
    serverSocket.listen(1) # server begins listening for incoming TCP requests
    connectionP.connect((SERVER_HOST, SERVER_PORT))
    print("ftpclient.c connected successfully to ftpserver.c - connectionP established")
    client_command = COMMAND + " " + FILE_NAME + " " +  str(DATA_PORT)
    # 6. ftpclient sends a command (-l (list) or -g <FILENAME> (get)) on connection P.
    connectionP.send(client_command.encode('utf-8'))

    connectionQ, addr = serverSocket.accept() # server waits on accept() for incoming requests, new socket created on return
    print("ftpserver.c connected successfully to ftpclient.py - connectionQ established")
    if G_COMMAND: # did the user send the '-g' command?
        fileSize = connectionQ.recv(500).decode('utf-8').strip()# recv the size of the file that the client wants
        connectionQ.send("OKAY".encode('utf-8')) # send back OKAY - to prevent part of the file being sent in with the fileSize buffer sent earlier
        if not fileSize: # was the size of the file sent back?
            server_response = connectionP.recv(500).decode('utf-8').strip() # receives error message from ftpserver.c on connectionP
            print(server_response)
        else: # size of the file was sent back
            fileBuffer = connectionQ.recv(int(fileSize)).decode('utf-8').strip() # cast fileSize as an int, and receive the buffer containing our file data
            with open("COPY-" + FILE_NAME, 'w') as my_file: # prepend 'Copy' to our file_name and open this file in write mode
                my_file.write(fileBuffer) # write the contents of the file buffer received to the file we open up
            print("Finished writing file!")
    else: # user has sent the '-l' command to receive the names of each file in the current directory of ftpserver.c
        server_response = connectionQ.recv(500).decode('utf8', 'ignore').strip() # receive the names of the files
        print("\nCurrent directory of ftpserver.c:\n\n" + server_response)
    connectionQ.close() # close connectionQ
    connectionP.close() # ftpclient closes connection P and terminates

if __name__ == "__main__":
    main()