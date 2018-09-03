import select, socket, sys, os
import signal
import time
# This function handles all SIGINT (ctrl+c) action and exits the program.
def sigint_handler(signum, frame):
    print('Server is exiting')
    sys.exit()

signal.signal(signal.SIGINT, sigint_handler) # Set up our signal handler to handle ctrl+c

def main():
    if len(sys.argv[1:]) != 1:
        print('Only 1 argument needed (the port #). Please try again. ')
        quit()
    else:
        serverPort = int(sys.argv[1])
        try:
            serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create TCP welcoming socket
            serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            serverSocket.bind(("", serverPort)) # bind our port number to our socket
            print("Socket successfully created")
        except socket.error as err:
            print("Socket created failed with error ", err)
            sys.exit()
        chat_name = input("Enter in the server's chat name: ")
        server_prompt = chat_name + "> "
        serverSocket.listen(1) # server begins listening for incoming TCP requests
        print("The server is ready to receive")
        while 1: # loop forever and accept connections
            connectionSocket, addr = serverSocket.accept() # server waits on accept() for incoming requests, new socket created on return
            print("Client has connected")
            while 1:
                client_msg = connectionSocket.recv(500).decode('utf8').strip() # recv client's username
                if client_msg and "Exiting" not in client_msg:
                    print(client_msg)
                    print(server_prompt, end='')
                    server_input = input() # get input from the user
                    if server_input == "\quit":
                        server_msg = "Server has closed the connection"
                        connectionSocket.send(server_msg.encode('utf-8'))
                        break # close the socket
                    else:
                        server_msg = server_prompt + server_input
                        connectionSocket.send(server_msg.encode('utf-8'))
                else: # Client has sent a message that they're closing the connection to the server
                    print("The client has closed the connection")
                    break # Close the socket
            connectionSocket.close()
        
if __name__ == "__main__":
	main()