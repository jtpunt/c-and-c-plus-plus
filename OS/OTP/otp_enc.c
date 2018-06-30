// 1. This program connects to otp_enc_d, and asks it to perform a one-time pad style encryption.
// 2. By itself, otp_enc doesn't do the encryption - otp_end_d does. 
// 3. When otp_receives the ciphertext back from otp_enc_d, it should output it to stdout. Thus, otp_enc can be launched in any
//   of the following methods,and should send its outut appropriately.
// 4. If otp_enc receives key or plaintext file with ANY bad characters in them, or the key file is shorter than the plaintext, 
//    then it should terminate, send appropriate error text to stderr, and set the exit value to 1.
// 5. otp_enc should NOT be able to connecT to otp_dec_d, even if it tries to connect n the correct port - you'll need to have the
//    programs reject each other. If this happens, otp_enc should report the rejection to stderr and then terminate itself.
// 6. In more detail: if otp_enc cannot connect to the otp_dec_d server, for any reason (including that it has accidentally tried
//    to connect to the otp_dec_d server), it should report this error to stderr with the attempted port, and set the exit value to 2.
//    2. Otherwise, upon successfully running and terminating, otp_enc should set the exit value to 0.
// 7. Again, any and all error text must be output to stderr(not into plaintext or ciphertext file).

// The syntax is: otp_enc plaintext key port
//                otp_enc myplaintext mykey 57171
//			      otp_enc myplaintext mykey 57171 > myciphertext
// 				  otp_enc myplaintext mykey 57171 > myciphertext &
// 	- in this syntax, plaintext is the name of a file in the current directory that contains the plaintext you wish to encrypt.
//  - similarly, key contains the encrpytion key you wish to use to encrpyt the text. 
//  - port is the port that otp_enc should attempt to connect to otp_enc_d on.

// This file is the client
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <netdb.h> 

// void error(const char *msg) { perror(msg); exit(0); } // Error function used for reporting issues

// int main(int argc, char *argv[]){
// 	int socketFD, portNumber, charsWritten, charsRead;
// 	struct sockaddr_in serverAddress;
// 	struct hostent* serverHostInfo;
// 	char buffer[256];
//     // CHANGE TO < 4 FOR THE PLAINTEXT FILE
// 	if(argc < 3){ // Check usage & args
// 		fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(0); 
// 	} 
// 	// GET THE SIZE OF THE FILE, STORE IT
// 	// IF THE KEY FILE SIZE < PLAINTEXT FILE SIZE, OUTPUT ERROR
// 	// OPEN THE PLAINTEXT FILE
// 	// IF PLAINTEXT ERRORS ON OPEN, OUTPUT ERROR
// 	// VALIDATE THE CONTENTS OF THE PLAINTEXT FILE
// 	// IF PROBLEM VALIDATING, OUTPUT ERROR 
// 	// 1. This program connects to otp_enc_d, and asks it to perform a one-time pad style encryption.
// 	// 2. By itself, otp_enc doesn't do the encryption - otp_end_d does. 
// 	// Set up the server address struct
// 	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
// 	portNumber = atoi(argv[2]); // Get the port number, convert to an integer from a string
// 	serverAddress.sin_family = AF_INET; // Create a network-capable socket
// 	serverAddress.sin_port = htons(portNumber); // Store the port number
// 	serverHostInfo = gethostbyname(argv[1]); // Convert the machine name into a special form of address
// 	if(serverHostInfo == NULL){ 
// 		fprintf(stderr, "CLIENT: ERROR, no such host\n"); 
// 		exit(0); 
// 	}
// 	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

// 	// Set up the socket
// 	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
// 	if(socketFD < 0){
// 		error("CLIENT: ERROR opening socket");
// 	}
// 	// 5. otp_enc should NOT be able to connec to otp_dec_d, even if it tries to connect to the correct port - you'll need to have the
// 	//    programs reject each other. If this happens, otp_enc should report the rejection to stderr and then terminate itself.
// 	// 6. In more detail: if otp_enc cannot connect to the otp_dec_d server, for any reason (including that it has accidentally tried
// 	//    to connect to the otp_dec_d server), it should report this error to stderr with the attempted port, and set the exit value to 2.
// 	//    Otherwise, upon successfully running and terminating, otp_enc should set the exit value to 0.
// 	// Connect to server
// 	if(connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){// Connect socket to address
// 		error("CLIENT: ERROR connecting");
// 	}
// 	// Get input message from user
// 	printf("CLIENT: Enter text to send to the server, and then hit enter: ");
// 	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
// 	fgets(buffer, sizeof(buffer) - 1, stdin); // Get input from the user, trunc to buffer - 1 chars, leaving \0
// 	buffer[strcspn(buffer, "\n")] = '\0'; // Remove the trailing \n that fgets adds

// 	// Send message to server
// 	charsWritten = send(socketFD, buffer, strlen(buffer), 0); // Write to the server
// 	if(charsWritten < 0){
// 		error("CLIENT: ERROR writing to socket");
// 	}
// 	if(charsWritten < strlen(buffer)){
// 		printf("CLIENT: WARNING: Not all data written to socket!\n");
// 	}
// 	// 3. When otp_receives the ciphertext back from otp_enc_d, it should output it to stdout. Thus, otp_enc can be launched in any
// 	//   of the following methods,and should send its outut appropriately.
// 	// The syntax is: otp_enc plaintext key port
// 	//                otp_enc myplaintext mykey 57171
// 	//			      otp_enc myplaintext mykey 57171 > myciphertext
// 	// 				  otp_enc myplaintext mykey 57171 > myciphertext &

// 	// Get return message from server
// 	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
// 	charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read data from the socket, leaving \0 at end
// 	// 4. If otp_enc receives key or plaintext file with ANY bad characters in them, or the key file is shorter than the plaintext, 
// 	//    then it should terminate, send appropriate error text to stderr, and set the exit value to 1.
// 	if(charsRead < 0){
// 		fprintf(stderr, "CLIENT: ERROR reading from socket");
// 		// EXIT(1)
// 	}
// 	printf("CLIENT: I received this from the server: \"%s\"\n", buffer);

// 	close(socketFD); // Close the socket
// 	return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>
#include "otp_common.h"

#define CLIENT_TYPE 1		// encrypt == 1; decrypt == 0

int main(int argc, char **argv)
{
	int sockfd;						// socket file descriptor
	int portNum;					// port number
	struct sockaddr_in servAddr;	// internet address struct
	struct hostent *server;			// host computer

	struct stat plaintextStat, keyStat;	// file statistics for checking length
	long ptextSize, keySize;		// for storing file lengths
	int ptextfd, keyfd;		// file descriptors for plaintext and key files
	int readPtext, readKey;			// verify that read works

	int clientType = CLIENT_TYPE;	// encrypt == 1; decrypt == 0
	int serverType;
	int sendBytes, recvBytes;

	char buffer[BUFFER_SIZE];
	bzero(buffer, sizeof(buffer));

	// check for correct number of arguments
	if (argc != 4)
	{
		fprintf(stderr, "Usage: %s plaintext key port\n", argv[0]);
		exit(0);
	}

	// check file sizes for plaintext file and key
	stat(argv[1], &plaintextStat);
	ptextSize = plaintextStat.st_size;
	stat(argv[2], &keyStat);
	keySize = keyStat.st_size;
	// fprintf(stderr, "%ld\n", ptextSize);
	if (keySize < ptextSize)	// key too short
	{
		fprintf(stderr, "Error: key '%s' is too short\n", argv[2]);
		exit(1);
	}

	// open plaintext file
	ptextfd = open(argv[1], O_RDONLY);
	if (ptextfd == -1)
	{
		fprintf(stderr, "Error: cannot open plaintext file '%s'\n", argv[1]);
		exit(1);
	}

	// verify contents of plaintext file
	char plaintext[ptextSize];
	bzero(plaintext, sizeof(plaintext));
	readPtext = read(ptextfd, plaintext, ptextSize);
	if (readPtext < 0)
	{
		fprintf(stderr, "Error: cannot read plaintext file '%s'\n", argv[1]);
		exit(1);
	}
	plaintext[ptextSize - 1] = '\0';
		// replace trailing newline with null char
	if (verifyInput(plaintext) != 1)
	{
		fprintf(stderr, "Error: '%s' contains invalid characters\n", argv[1]);
		exit(1);
	}

	// open key file
	keyfd = open(argv[2], O_RDONLY);
	if (keyfd == -1)
	{
		fprintf(stderr, "Error: cannot open key file '%s'\n", argv[2]);
		exit(1);
	}

	// verify contents of key file
	char key[keySize];
	bzero(key, sizeof(key));
	readKey = read(keyfd, key, keySize);
	if (readKey < 0)
	{
		fprintf(stderr, "Error: cannot read key file '%s'\n", argv[2]);
		exit(1);
	}
	key[keySize - 1] = '\0';		// replace trailing newline with null char
	if (verifyInput(key) != 1)
	{
		fprintf(stderr, "Error: '%s' contains invalid characters\n", argv[2]);
		exit(1);
	}

	// create the socket and get file descriptor
	// use AF_INET for IP
	// use SOCK_STREAM for TCP
	// use 0 for IP
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "Error: %s socket creation failed\n", argv[0]);
		exit(1);
	}

	// set up address
	// client connecting to server
	server = gethostbyname("localhost");
	if (server == NULL)
	{
		fprintf(stderr, "Error: %s could not resolve server host name\n",
			argv[0]);
		exit(1);
	}

	// set up socket address struct
	// client connecting to server
	portNum = atoi(argv[3]);
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(portNum);
	memcpy(&servAddr.sin_addr, server->h_addr_list[0], server->h_length);

	// connect the socket to the server
	if (connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
	{
		// no encrypt server on port
		fprintf(stderr, "Error: %s could not contact otp_enc_d on port %d\n",
			argv[0], portNum);
		exit(2);
	}

	char serverString[] = "server";		// for error messages

	// check that both server and client are encrypt type
	// both sides do this check, but server sends its response to the client
	// client is the one to close the connection if there is a type mismatch
	// verify that serverType == clientType
	// send client type to server
	sendBytes = send(sockfd, &clientType, sizeof(clientType), 0);
	if (sendBytes < 0)
	{
		sendError(argv[0], serverString, 1);
	}
	// receive server type from server
	recvBytes = recv(sockfd, &serverType, sizeof(serverType), 0);
	if (recvBytes < 0)
	{
		receiveError(argv[0], serverString, 1);
	}
	// server at port is not encrypt type
	if (clientType != serverType || clientType != 1 || serverType != 1)
	{
		fprintf(stderr, "Error: %s could not contact otp_enc_d on port %d\n",
			argv[0], portNum);
		close(sockfd);
		exit(2);
	}
	// receive server reponse to type check
	bzero(buffer, sizeof(buffer));
	recvBytes = recv(sockfd, buffer, sizeof(buffer), 0);
	if (recvBytes < 0)
	{
		receiveError(argv[0], serverString, 1);
	}
	if (strcmp(buffer, "type match") != 0)
	{
		fprintf(stderr, "Error: %s cannot find otp_enc_d on port %d\n",
			argv[0], portNum);
		close(sockfd);
		exit(2);
	}

	// file sizes verified and file contents verified by otp_enc
	// connected and both client and server are encrypt type

	// server will do another file size check on its end and send response back
	// client is the one to close connection if key size is too small
	// send plaintext file size
	sendBytes = send(sockfd, &ptextSize, sizeof(ptextSize), 0);
	if (sendBytes < 0)
	{
		sendError(argv[0], serverString, 1);
	}
	// send key file size
	sendBytes = send(sockfd, &keySize, sizeof(keySize), 0);
	if (sendBytes < 0)
	{
		sendError(argv[0], serverString, 1);
	}
	// receive server response to key size check
	bzero(buffer, sizeof(buffer));
	recvBytes = recv(sockfd, buffer, sizeof(buffer), 0);
	if (recvBytes < 0)
	{
		receiveError(argv[0], serverString, 1);
	}
	if (strcmp(buffer, "key ok") != 0)
	{
		fprintf(stderr, "Error: key '%s' is too short\n", argv[2]);
		close(sockfd);
		exit(1);
	}

	// pass both client and server encrypt type and key size checks

	// send plaintext to server
	sendBytes = send(sockfd, plaintext, sizeof(plaintext), 0);
	if (sendBytes < 0)
	{
		sendError(argv[0], serverString, 1);
	}

	// send key to server
	sendBytes = send(sockfd, key, sizeof(key), 0);
	if (sendBytes < 0)
	{
		sendError(argv[0], serverString, 1);
	}

	// server encrypts plaintext and sends ciphertext back
	char ciphertext[ptextSize];
	bzero(ciphertext, sizeof(ciphertext));
	recvBytes = recv(sockfd, ciphertext, sizeof(ciphertext), MSG_WAITALL);
	if (recvBytes < 0)
	{
		receiveError(argv[0], serverString, 1);
	}

	// print ciphertext to stdout, and add trailing newline
	fprintf(stdout, "%s\n", ciphertext);

	close(sockfd);

	return 0;
}