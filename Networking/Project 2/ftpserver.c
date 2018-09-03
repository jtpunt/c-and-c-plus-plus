// Name: Jonathan Perry
// Date: 8/12/2018
// Class: CS 372
// Project: Project 2
#include <dirent.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#define BUFFER_SIZE 500
#define MAX_NAME_LENGTH 10

// Function Prototypes
int createSocket(char *);
struct sockaddr_in * createSocketType(int, struct hostent*);
void connectSocket(int connectionP, struct sockaddr_in *servAddr, int portNumber);
void sendData(int socket, void *buffer, size_t length, int flags, char* args, int exitValue);
void recvData(int socket, void *buffer, size_t length, int flags, char* args, int exitValue);
void checkFile(int, char *);
void checkRedir(int , char*);
char* listDirContents();
char* getTokenN(char*, int);
void checkCommands(int socket, char *, char*);
int getDigits(int);
char* getFileContents(int socket, char* file_name, size_t*);
// This function creates a socket file descriptor and returns it. 
// If any errors occur while creating the socket file descriptor, an error message and the
// program name sent in to this function as an argument is printed to the screen.
int createSocket(char * cmd){
	int connectionP;
	if ((connectionP = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		fprintf(stderr, "Error: %s socket creation failed\n", cmd);
		exit(EXIT_FAILURE);
	}
	return connectionP;
}
// This function creates a pointer to socket variable, where it sets the address family to recognize IPv4 addresses, 
// sets the port number specified by the first argument, and sets the address specifed by the second argument.
struct sockaddr_in * createSocketType(int portNumber, struct hostent *server){
	struct sockaddr_in *servAddr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	assert(servAddr != 0);
	servAddr->sin_family = AF_INET; // Create a network-capable socket for IPv4
	servAddr->sin_port = htons(portNumber); // Store the port number
	memcpy(&servAddr->sin_addr, server->h_addr_list[0], server->h_length);
	return servAddr;
}
// This function connects the client to the server by using the socket file descripter sent in as argument 1,
// the socket variable sent in from argument 2 that contains information about the server we want to connect to.
// If there's an error connection, an error message specifying the port number we attempted to connect to is printed 
// to the console.
void connectSocket(int socket, struct sockaddr_in *servAddr, int portNumber){
	if (connect(socket, (struct sockaddr *) servAddr, sizeof(*servAddr)) < 0){ // try to connect to otp_enc_d
		printf("Error when connecting! %s\n",strerror(errno));
		fprintf(stderr, "Error: could not contact server on port %d\n", portNumber);
		close(socket);
		exit(2);
	}
}

// This function is used to send data between the client and server. If the exitValue is not -1,
// then the function will call exit with the exitValue argument passed in.
void sendData(int socket, void *buffer, size_t length, int flags, char* args, int exitValue){
	if((send(socket, buffer, length, flags)) == 0){
		fprintf(stderr, "Error: File %s Failed Sending Data\n", args);
		if(exitValue != -1){
			exit(exitValue);
		}
	}
}

// This function is used to receive data between the client and server. If the exitValue is not -1,
// then the function will call exit with the exitValue argument passed in.
void recvData(int socket, void *buffer, size_t length, int flags, char* args, int exitValue){
	if ((recv(socket, buffer, length, flags)) == 0){
		fprintf(stderr, "Error: File %s Failed Receiving Data\n", args);
		if(exitValue != -1){
			exit(exitValue);
		}
	}
}
// Prints output to the console and then exits the program if the file was not opened successfully.
void checkFile(int fileDesc, char *fileName){
	if (fileDesc == -1){ // did the file not open successfully?
		fprintf(stderr, "cannot open %s for input\n", fileName);
		exit(EXIT_FAILURE);
	}
}
// Prints output to the console and then exits the program if the stdin/stdout redirection was successful
void checkRedir(int redirResult, char* fileName){
	if (redirResult == -1){ // was the redirection successful?
		fprintf(stderr, "cannot open %s for input\n", fileName);
		exit(EXIT_FAILURE);
	}
}
// This function returns the names of each file in the current directory of ftpserver.c
char* listDirContents(){
	pid_t spawnPid;
	char* buffer = malloc(BUFFER_SIZE * sizeof(char));

	int out_pipe[2], saved_stdout = dup(STDOUT_FILENO); // create an aliased file descriptor
	pipe(out_pipe); // make a pipe
	if(spawnPid = fork() == 0){ // fork from this process - child process
		checkRedir(dup2(out_pipe[1], STDOUT_FILENO), "STDOUT_FILENO"); // check to see if the stdout redirection was successful
		execlp("/bin/ls", "ls", NULL); // stdout from ls is redirected to the "test" file
	}else if(spawnPid == -1){ // did the fork fail?
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else{ // parent process
		memset(buffer, '\0', BUFFER_SIZE * sizeof(char));
		read(out_pipe[0], buffer, BUFFER_SIZE);
		return buffer;
	}
}
// Returns a pointer to the nth token as specified by the 2nd argument - nth_token
char* getTokenN(char* buffer, int nth_token){
	assert(buffer != NULL);
	int tokenCount = 0;
   	char* prevToken = NULL, *token = strtok(buffer, " "); // -g
	while(token != NULL && ++tokenCount <= nth_token){ // loop until we have extracted the 2nd token, the FILENAME specified by the client to have sent to them
		prevToken = token; // Store the current token, as eventually the last token returned will be NULL
		token = strtok(NULL, " ");
	}
	return prevToken; // prevToken is our FILE_NAME
}
// This function validates commands sent by ftpclient.c and handles the response back to ftpclient.c
// If the user has typed in the '-g' command, then ftpserver.c will need to connect to ftpclient.c on a seperate connection to transfer files.
// If the user has typed in the '-l' command, then no 2nd connection will need to be established. Send ftpclient.c the name of each file in ftpserver's current directory
void handleCommands(int connectionP, char* buffer, char* ip){
	char *ptr = NULL,  *dirPtr, *fileName = NULL;
	char dirContents[BUFFER_SIZE], backup[BUFFER_SIZE];		
	struct sockaddr_in *servAddr = NULL;
	struct hostent *server = NULL;
	int connectionQ, portNumber;
	size_t fileSize = 0;
	memset(dirContents, '\0', sizeof(dirContents));
	server = gethostbyname(ip);
	connectionQ = createSocket("./ftpserver.c"); // sends the program name 
	strcpy(backup, buffer);
	portNumber = atoi(getTokenN(buffer, 3));
	strcpy(buffer, backup);
	servAddr = createSocketType(portNumber, server);
	connectSocket(connectionQ, servAddr, portNumber); // 7.2a ftpserver initiates a TCP data connection with ftpclient on <DATA_PORT> (call this connection Q)
	printf("ftpserver.c successfully connected to ftpclient.py - connectionQ established\n");
	// 7.1 if ftpcleint sent an invalid command:
	if(buffer == NULL){
		// 7.1a ftpserver sends an error message to ftpclient on Connection P, and ftpclient displays the message on screen
		printf("ERROR: buffer is NULL\n");
	}else{ // 7.2 otherwise
    	dirPtr = listDirContents();
    	strcpy(dirContents, dirPtr);
    	free(dirPtr);
    	// 7.2b if ftpclient has sent the -l command, ftpserver sends its directory to ftpclient on connection Q, and ftpclient displays the directory on-screen
    	if(strstr(buffer, "-l")){ // is '-l' somewhere in the users input?
    		printf("Sending directory contents\n");
    		sendData(connectionQ, &dirContents, sizeof(dirContents), 0, NULL, 1);
    	}
    	// 7.2c if ftpclient has sent -g <FILENAME>, ftpserver validates FILENAME, and either/or
    	else if(strstr(buffer, "-g")){ // is '-g' somewhere in the users input? 
    		fileName = getTokenN(buffer, 2);
    		if(strstr(dirContents, fileName)){ // is the file name in our current directory?
    			// 7.2c-1 Sends the contents of FILENAME on connection Q. ftpclient saves the file in the current default directory and displays a "transfer complete" message on-screen
    			printf("file \'%s\' was found!\n\n", fileName);
    			ptr = getFileContents(connectionQ, fileName, &fileSize); // EXTRA CREDIT - This program can transfer files additional to text files
    			char file[fileSize]; // Holds an appropriate amount of digits to represent the # of bytes in the file
    			memset(file, '\0', sizeof(file));
    			strcpy(file, ptr);
    			printf("Sending file contents\n");
    			sendData(connectionQ, &file, fileSize, 0, NULL, 1);
    			free(ptr);
    		}else{ // 7.2c-2 Sends an appropriate error message ("File not found", etc) to ftpclient on connection P, and ftpclient displays the message on-screen.
    			printf("file \'%s\' was not found!\n\n", fileName);
    			sendData(connectionP, "ftpserver: File Not Found", 26, 0, NULL, 1);
    		}
    	}else{ // user has entered an invalid command
    		printf("Invalid Command Entered by Client!: %s\n", buffer);
    		sendData(connectionP, "ftpserver: Invalid Command", 27, 0, NULL, 1);
    	}
	}
	free(servAddr);
	close(connectionQ); // Close the connection socket
}
// This function counts the number of digits that are in the integer passed in to this function - new_length, so that a char array can be initialized to hold each digit
int getDigits(int new_length){
    int n = new_length, count = 0;
    while(n != 0){
    	n /= 10;
    	++count;
    }
    return count;
}
// Gets the contents and file byte size of the file name passed in and sends the file byte size to ftpclient.py
char* getFileContents(int connectionP, char* file_name, size_t* fileSize) {
	FILE* fptr = NULL;
    char *fileContents = NULL;
    char server_resp[BUFFER_SIZE];
    struct stat fileStat;
    memset(server_resp, '\0', sizeof(server_resp));

    if((fptr = fopen(file_name, "r")) == NULL){ // can we open the file?
        perror("ERROR: unable to open file");
    }else{ // the file was opened correctly
    	stat(file_name, &fileStat);
    	size_t mySize = fileStat.st_size;
    	if(mySize > 0){
    		fileContents = malloc(sizeof(char) * (mySize + 1));
    		memset(fileContents, '\0', sizeof(fileContents));
            *fileSize = fread(fileContents, sizeof(char), mySize, fptr);
			char str[getDigits(*fileSize)]; // char array needs to be able to hold the same # of digits as the size of the file we just read
			sprintf(str, "%zu", *fileSize); // writes the size_t as a c-string to the str variable
            if (ferror(fptr) != 0){
                fputs("ERROR: error while reading file", stderr);
            }else{
                fileContents[*fileSize++] = '\0'; // add null terminator to c-string
                sendData(connectionP, str, sizeof(str), 0, NULL, 1); // send the file size to the client 
                recvData(connectionP, server_resp, sizeof(server_resp), 0, NULL, 1); // client sends back - OKAY - indicated that theyre ready to receive the file
            }
    	}
    }
    fclose(fptr); // closes the file
    return fileContents; // returns the contents of the file
}

int main(int argc, char **argv){
	int listenSocketFD, connectionP, portNumber;				
	socklen_t sizeofClientInfo;		
	struct sockaddr_in serverAddress, clientAddress;
	pid_t spawnPid;		
	char buffer[BUFFER_SIZE];
	// 1. ftpserver starts on Host A, and validates command-line parameters <SERVER_PORT>
	if (argc != 2){
		fprintf(stderr, "Usage: %s listening_port\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress));  // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Any address is allowed for connection to this process

	// Set up the socket
	if ((listenSocketFD = socket(AF_INET, SOCK_STREAM, 0)) < -1){ // Create the socket
		fprintf(stderr, "ERROR opening socket\n");
		exit(
			EXIT_FAILURE);
	}
	int on = 1;
	if(setsockopt(listenSocketFD, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0){ // set UNIX up so that we can reuse ports
		fprintf(stderr, "ERROR on reusing port number\n");
		exit(EXIT_FAILURE);
	}
	// Enable the socket to begin listening by connecting socket to port
	if (bind(listenSocketFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
		fprintf(stderr, "ERROR on binding\n");
		exit(EXIT_FAILURE);
	}

	// Flip the socket on - it can now receive up to 5 connections
	if (listen(listenSocketFD, 5) < 0){
		fprintf(stderr, "ERROR on listening\n");
		exit(EXIT_FAILURE);
	}
	while (1){ // Keep looping to accept incoming connections from clients
		sizeofClientInfo = sizeof(clientAddress);
		// 4. ftpserver and ftpclient establish a TCP controll connection on <SERVER_PORT>. 
		if ((connectionP = accept(listenSocketFD, (struct sockaddr *) &clientAddress, &sizeofClientInfo)) < 0){
			fprintf(stderr, "ERROR on accept\n");
			break; // break to end the connection with the client
		}
		printf("ftpclient.py successfully connected to ftpserver.c- connectionP established\n");
		char *ip = inet_ntoa(clientAddress.sin_addr); // get the ip address of ftpclient.py
		if (spawnPid = fork() == 0){ // fork and let the child process handle the rest
			char buffer[BUFFER_SIZE];
			memset(buffer, '\0', sizeof(buffer));
			// 5. ftpserver waits on connection P for ftpclient to send a command
			recvData(connectionP, &buffer, sizeof(buffer), 0, argv[0], -1); 
			handleCommands(connectionP, buffer, ip);
			close(connectionP); // Close the existing socket which is connected to the client
			connectionP = -1;
			exit(EXIT_SUCCESS);
		}else if (spawnPid == -1){ // did the fork fail?
			close(connectionP); // Close the existing socket which is connected to the client
			connectionP = -1;
			fprintf(stderr, "ERROR on fork call\n");
		}else{ // parent process
			close(connectionP); // Close the existing socket which is connected to the client
			connectionP = -1;
			wait(NULL);
		}
	} // 9. ftpserver repeats from 2 (above) until terminated by a supervisor (SIGINT)
	close(listenSocketFD); // Close the listening socket

	return 0;
}