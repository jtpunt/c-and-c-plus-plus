// 1. This program will run in the background as a daemon. Upon execution,  otp_enc_d must output an error if it cannot be run due to a
//    network error, such as the ports being unavailable.
// 2. Its function is to perform the actual encoding, as descripted above in the wikipedia quote.
// 3. The program will listen on a particular port/socket, assigned when it is first ran.
// 4. When a connection is made, otp_enc_d must call accept() to generate the socket used for actual communication,
//    and then use a seperate process to handle the rest of the transaction, which will occur on the newly accepted socket.
// 5. This child process of otp_enc_d must first check to make sure it is communicating with otp_enc.
// 6. After reviewing that the connection to otp_enc_d is coming from otp_enc, this child receives from otp_enc plaintext
//    and a key via the communication socket (not the original listen socket).
// 7. The otp_enc_d child will then write back the ciphertext to the otp_enc process that it is connected to via the same 
//    communication socket. 
// 8. Note that the key passed in must be at least as big as the plaintext.
// 9. Your version of otp_enc_d must support up to 5 concurrent socket connections running at the same time; this is different
//    than the # of processes that could queue up on your listening socket (which is specified in the 2nd parameter of the listen() call)
// 10. Again, only in the child process will the actual encryption take place, and the ciphertext be written back: the original daemon
//     process continues listening for new connections, not encrypting data.
// 11. In terms of creating that child process as described above, you may either create with fork() a new process every time a connection
//     is made, or set up a pool of five processes at the beinning of the program, befefore connections are allowed, to handle your encryption tasks.
// 12. As above, your system must be able to do five seperate encryptions at once, using either method you choose.
// 13. In all error situations, this program must output errors to stderr as appropritae (see grading script for details), but should not crash or
//     otherwise exit, unless the errors happens when the program is starting up (i.e. are apart of the networking start up protocols like bind()).
// 14. If given bad input, once running, otp_enc_d should recognize the bad input, report an error to stderr, and continue to run.
// 15. Generally speaking, though, this daemon shouldn't receive bad input, since that should be discovered and handled in the client first.
// 16. All error text must be output to stderr.
// 17. This program, and the other 3 network programs, should use "localhost" as the target IP address/host.
// 18. This make them use the actual computer they all share as the target for the networking connections.

// Use this syntax for otp_enc_d: otp_enc_d listening_port
// 	- listening_port is the port that otp_enc_d should lsiten on. You will always start otp_enc_d in the background, as follows (the port 57171
//    is just a example; your should be able to use any port): otp_enc_d 57171 &

// This file is the server that receives the file 
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h> 
// #include <sys/socket.h>
// #include<sys/wait.h>
// #include <netinet/in.h>
// void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues

// int main(int argc, char *argv[]){
// 	int listenSocketFD, establishedConnectionFD, portNumberber, charsRead, status;
// 	socklen_t sizeOfClientInfo;
// 	char buffer[256];
// 	spawnPid_t spawnspawnPid;
// 	struct sockaddr_in serverAddress, clientAddress;

// 	if (argc < 2){ // Check usage & args
// 		// can use dup2 if needed to redirect stdxxx to stderr etc.
// 		fprintf(stderr, "USAGE: %s port\n", argv[0]); 
// 		exit(1); 
// 	} 

// 	// 3. The program will listen on a particular port/socket, assigned when it is first ran.
// 	// Set up the address struct for this process (the server)
// 	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
// 	portNumberber = atoi(argv[1]); // Get the port number, convert to an integer from a string
// 	serverAddress.sin_family = AF_INET; // Create a network-capable socket
// 	serverAddress.sin_port = htons(portNumberber); // Store the port number
// 	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process
// 	// CHANGE THE ABOVE to only allow connections

// 	// 1. This program will run in the background as a daemon. Upon execution,  otp_enc_d must output an error if it cannot be run due to a
// 	//    network error, such as the ports being unavailable.
// 	// Set up the socket
// 	if ((listenSocketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0){  // Create the socket
// 		fprintf(stderr, "ERROR opening socket\n");
// 	}
// 	// Enable the socket to begin listening
// 	if(bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){ // Connect socket to port
// 		fprintf(stderr, "ERROR on binding\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	if(listen(listenSocketFD, 5) < 0){ // Flip the socket on - it can now receive up to 5 connections
// 		fprintf(stderr, "ERROR on listening.\n");
// 	}
// 	// 4. When a connection is made, otp_enc_d must call accept() to generate the socket used for actual communication,
// 	//    and then use a seperate process to handle the rest of the transaction, which will occur on the newly accepted socket.
// 	// Accept a connection, blocking if one is not available until one connects
// 	while(1){
// 		sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
// 		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
// 		// 5. This child process of otp_enc_d must first check to make sure it is communicating with otp_enc.
// 		if (establishedConnectionFD < 0){ 
// 			fprintf(stderr,"ERROR on accept\n");
// 		}

// 		// FORK HERE 
// 		spawnspawnPid = fork();
// 		if (spawnspawnPid == 0){	// child process
// 			charsRead = send(establishedConnectionFD, "I am the server, and I got your message", 39, 0); // Send success back
// 			if(charsRead < 0){
// 				fprintf(stderr,"ERROR writing to socket");
// 				exit(EXIT_FAILURE);
// 			}
// 			// 6. After reviewing that the connection to otp_enc_d is coming from otp_enc, this child receives from otp_enc plaintext
// 			//    and a key via the communication socket (not the original listen socket).
// 			// Get the message from the client and display it
// 			memset(buffer, '\0', 256);
// 			charsRead = recv(establishedConnectionFD, buffer, 255, 0); // Read the client's message from the socket
// 			// 8. Note that the key passed in must be at least as big as the plaintext.
// 			if(charsRead < 0){
// 				fprintf(stderr,"ERROR reading from socket\n");
// 			}
// 			// 7. The otp_enc_d child will then write back the ciphertext to the otp_enc process that it is connected to via the same 
// 			//    communication socket.
// 			printf("SERVER: I received this from the client: \"%s\"\n", buffer);
// 		}else if (spawnspawnPid == -1){ // did the fork fail?
// 			perror("fork error");
// 			exit(EXIT_FAILURE);
// 		}else{ // parent process
// 			printf("Closing establishedConnectionFD\n");
// 			close(establishedConnectionFD); // Close the existing socket which is connected to the client
// 			do {
// 				waitspawnPid(spawnspawnPid, &status, 0);
// 			}while(!WIFEXITED(status) && !WIFSIGNALED(status));
// 		}
// 		// 9. Your version of otp_enc_d must support up to 5 concurrent socket connections running at the same time; this is different
// 		//    than the # of processes that could queue up on your listening socket (which is specified in the 2nd parameter of the listen() call)
// 		// Send a Success message back to the client
// 	}

// 	close(listenSocketFD); // Close the listening socket
// 	return 0; 
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "otp_common.h"

#define SERVER_TYPE 1		// encrypt == 1; decrypt == 0

int main(int argc, char **argv){
	int listenSocketFD, establishedConnectionFD;		// socket file descriptors
	int portNumber;				// port number
	socklen_t sizeofClientInfo;			// size of address of client for accept()
	struct sockaddr_in serverAddress, clientAddress;	// internet address struct
	int optval;					// for setsockopt()

	int status;			// process status
	pid_t spawnPid;			// process id

	int serverType = SERVER_TYPE;	// encrypt == 1; decrypt == 0
	int clientType;
	int sendBytes, recvBytes;

	long ptextSize, keySize;
	char buffer[BUFFER_SIZE];
	bzero(buffer, sizeof(buffer));


	if (argc != 2){
		fprintf(stderr, "Usage: %s listening_port\n", argv[0]);
		exit(0);
	}
	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Any address is allowed for connection to this process
	// 	1. This program will run in the background as a daemon. Upon execution,  otp_enc_d must output an error if it cannot be run due to a
	// 	   network error, such as the ports being unavailable.
	// Set up the socket
	if ((listenSocketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		fprintf(stderr, "Error: server socket creation failed\n");
		exit(1);
	}
	// setup UNIX so that we can reuse ports
	optval = 1;
	setsockopt(listenSocketFD, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){ // Connect socket to port
		fprintf(stderr, "Error: server bind call failed\n");
		exit(1);
	}

	if (listen(listenSocketFD, 5) < 0){ // Flip the socket on - it can now receive up to 5 connections
		fprintf(stderr, "Error: server listen call failed\n");
		exit(1);
	}

	// loop and accept, wait for clients to contact
	while (1){
		sizeofClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
		// 4. When a connection is made, otp_enc_d must call accept() to generate the socket used for actual communication,
 		//    and then use a seperate process to handle the rest of the transaction, which will occur on the newly accepted socket.
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *) &clientAddress, &sizeofClientInfo); // Accept
		if (establishedConnectionFD == -1){
			fprintf(stderr, "Error: server accept call failed\n");
		}

		spawnPid = fork();	// fork the server process

		if (spawnPid == -1){	// failure to fork
			close(establishedConnectionFD);
			establishedConnectionFD = -1;
			fprintf(stderr, "Error: server fork failed\n");
		}

		if (spawnPid == 0){	// child process
			char clientString[] = "client";		// for error messages

			// Get the client type from the client as we need to verify that the connection to otp_enc_D is coming from ot_enc
			if ((recvBytes = recv(establishedConnectionFD, &clientType, sizeof(clientType), 0)) == 0){
				fprintf(stderr, "Error: %s could not receive from %s\n", argv[0], clientString);
			}
			// send server type to client
			if ((sendBytes = send(establishedConnectionFD, &serverType, sizeof(serverType), 0)) == 0){
				fprintf(stderr, "Error: %s could not send to %s\n", argv[0], clientString);
			}
			// server at port is not encrypt type
			if (clientType != serverType || clientType != 1 || serverType != 1){
				continue;	// client has probably already closed connection
			}else{
				// 6.1 After reviewing that the connection to otp_enc_d is coming from otp_enc, this child receives from otp_enc plaintext
				//    and a key via the communication socket (not the original listen socket).
				char response[] = "type match";
				if ((sendBytes = send(establishedConnectionFD, response, sizeof(response), 0)) < 0){
					sendErrorNoExit(argv[0], clientString);
				}
			}
			// 6.2 After reviewing that the connection to otp_enc_d is coming from otp_enc, this child receives from otp_enc plaintext
			//    and a key via the communication socket (not the original listen socket).
			if ((recvBytes = recv(establishedConnectionFD, &ptextSize, sizeof(ptextSize), 0)) < 0){
				receiveErrorNoExit(argv[0], clientString);
			}
			if ((recvBytes = recv(establishedConnectionFD, &keySize, sizeof(keySize), 0)) < 0){
				receiveErrorNoExit(argv[0], clientString);
			}
			// key size too small for plaintext
			if (keySize < ptextSize){
				continue;	// client has probably already closed connection
			}else{
				// send repsonse to client; client will check response
				char response[] = "key ok";
				if ((sendBytes = send(establishedConnectionFD, response, sizeof(response), 0)) < 0){
					fprintf(stderr, "Error: %s could not send to %s\n", argv[0],clientString);
				}
			}

			// pass both encrypt type and key size check

			// now receive plaintext from client
			char plaintext[ptextSize];
			bzero(plaintext, sizeof(plaintext));
			if ((recvBytes = recv(establishedConnectionFD, plaintext, sizeof(plaintext), MSG_WAITALL)) < 0){
				fprintf(stderr, "Error: %s could not receive from %s\n", argv[0], clientString);
			}

			// now receive key from client
			char key[keySize];
			bzero(key, sizeof(key));
			if ((recvBytes = recv(establishedConnectionFD, key, sizeof(key), MSG_WAITALL)) < 0){
				fprintf(stderr, "Error: %s could not receive from %s\n", argv[0], clientString);
			}

			// now encrypt the plaintext using the key
			char ciphertext[ptextSize];
			bzero(ciphertext, sizeof(ciphertext));
			encrypt(plaintext, key, ciphertext);

			// 7. The otp_enc_d child will then write back the ciphertext to the otp_enc process that it is connected to via the same 
 			//    communication socket.
			if ((sendBytes = send(establishedConnectionFD, ciphertext, sizeof(ciphertext), 0)) < 0){
				sendErrorNoExit(argv[0], clientString);
			}

			close(establishedConnectionFD);  // Close the existing socket which is connected to the client
			establishedConnectionFD = -1;

			exit(EXIT_SUCCESS);	
		}else{ // parent 
			// close client socket
			close(establishedConnectionFD);
			establishedConnectionFD = -1;
			// deal with zombies
			wait(NULL);
		}
	}

	close(listenSocketFD); // Close the listening socket

	return 0;
}