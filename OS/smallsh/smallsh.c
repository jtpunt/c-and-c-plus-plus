// Name: Jonathan Perry
// Date: 5/27/2018
// Class: CS 344 
#include <assert.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_CHARS 2048			// maximum 2048 characters per line
#define MAX_ARGS 512			// maximum 512 arguments


typedef struct cmdFlags {
	char *iFile;		// input filename
	char *oFile;		// output filename
	bool redirStdin;	// flag for stdin being redirected
	bool redirStdout;   // flag for stdout being redirected
	int numArgs;		// # of arguments entered by the user
	bool bgProcess;		// flag for a process/command to run in the background
	bool exitShellFlag; 
	pid_t processes[50];// list of processes running
	int numProcesses;
} cmdFlags;

struct sigaction sig_dfl, sig_ign, sig_stp;
char exitStatus[MAX_CHARS] = "There are no previous foreground processes.\n";


// function prototypes
void sigstp_handler(int);
char *readLine();
char **processInput(char *, cmdFlags *);
void checkFile(int, char *);
void executeCommand(char **, cmdFlags *);
void getFgStatus(pid_t pid, char *);
void getBgStatus(cmdFlags *);
void checkCommands(char**, cmdFlags *cmd);
void setCmdVariables(cmdFlags *cmd);
void setSigHandlers();

bool fg = false; // holds whether or not the process will run in the foreground, or background

int main(int numArgs, char **argv){
	bool exitShell = false;	
	cmdFlags *cmd = NULL;
	char *line = NULL;
	char **args;
	setSigHandlers(); 	// set signal handlers
	do{
		cmd = malloc(sizeof(struct cmdFlags));
		setCmdVariables(cmd);
		getBgStatus(cmd);
		printf(": "); 
		fflush(stdout);
		line = readLine();
		args = processInput(line, cmd);	
		checkCommands(args, cmd);
		exitShell = cmd->exitShellFlag;
		free(line);
		free(args);
		free(cmd);
	}
	while (!exitShell);

	return 0;
}
// This function is called when the sigtstp signal is used. When the signal is used, the program enters or exits foreground mode,
// where foreground mode allows the program to ignore and &, which then runs any future commands in foreground mode.
void sigstp_handler(int signum){
	if (!fg){ // We are not in foreground-only mode, enter this mode
    	char *message = "\nEntering foreground-only mode (& is now ignored)\n: ";
		write(STDOUT_FILENO, message, strlen(message));
    	fg = true;
	}else{ // we are in foreground-only mode, leave this mode.
    	char *message = "\nExiting foreground-only mode\n: ";
		write(STDOUT_FILENO, message, strlen(message));
		fg = false;
	}	
}
// This function reads in user input, stores it, and then returns a pointer to where the user input has been stored.
char *readLine(){
	char *line = NULL;
	ssize_t buffer = MAX_CHARS;
	getline(&line, &buffer, stdin);
	return line;
}
// This function processes of each the words/characters typed into by the user and stores them into an array.
char **processInput(char *line, cmdFlags *cmd){
	int bufferSize = MAX_ARGS;
	char **args = malloc(bufferSize * sizeof(char *));
	char *token;
	assert(args != NULL);

	token = strtok(line, " \n"); // tokenize the string
	while (token != NULL){
		if (strcmp(token, "&") == 0){ // is the process to be run in the background?
			cmd->bgProcess = true;
		}else if (strcmp(token, "<") == 0){ // stdin redirect?
			cmd->redirStdin = true;
			cmd->iFile = strtok(NULL, " \n"); // next token is the name of the input file
		}else if (strcmp(token, ">") == 0){	// stdout redirect?
			cmd->redirStdout = true;
			cmd->oFile = strtok(NULL, " \n"); // next token is the name of the output file
		}else{ // the token is an file name or argument
			args[cmd->numArgs++] = token;
			args[cmd->numArgs] = NULL;
		}
		token = strtok(NULL, " \n");
	}
	return args;
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
// Sets the stdin/stdout/background redirect up before executing the specified command
void executeCommand(char **args, cmdFlags *cmd){
	int inputFile, outputFile;	// file descriptors
	char fileName[MAX_CHARS] = "";

	if (cmd->redirStdin){ // redirect stdin?
		inputFile = open(cmd->iFile, O_RDONLY); // open the input file we need to redirect
		checkFile(inputFile, cmd->iFile); // check to see if the inputFile was opened successfully
		checkRedir(dup2(inputFile, 0) , cmd->iFile); // check to see if the stdin redirection was successful
	}else if (cmd->bgProcess || fg){	// background process indicated?
		inputFile  = open("/dev/null", O_RDONLY); // open /dev/null to redirect all stdin to
		checkFile(inputFile, "/dev/null"); // check to see if the inputFile was opened successfully
		checkRedir(dup2(inputFile , 0), "/dev/null"); // check to see if the stdin redirection was successful
	}
	if (cmd->redirStdout){ 	// redirect output?
		outputFile = open(cmd->oFile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // open the output file we need to redirect
		checkFile(outputFile, cmd->oFile); // check to see if the outputFile was opened successfully
		checkRedir(dup2(outputFile, 1), cmd->oFile); // check to see if the stdout redirection was successful
	}
	execvp(args[0], args);
	fprintf(stderr, "%s: no such file or directory\n", args[0]); // was a valid command entered?
	exit(EXIT_FAILURE);
}
// Prints out the exit value or signal number of the (foreground) process id passed in.
void getFgStatus(pid_t pid, char *exitStatus){
	int status;
	waitpid(pid, &status, 0);
	if(WIFEXITED(status)){
		sprintf(exitStatus, "exit value %d", WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status)){
		sprintf(exitStatus, "terminated by signal %d", WTERMSIG(status));
		printf("%s\n", exitStatus);
		fflush(stdout);
	}
}
// Prints out the process id of the completed (background) process along with the exit value or signal number of that process
void getBgStatus(cmdFlags *cmd){
	pid_t bgPid;
	int status;
	bgPid = waitpid(-1, &status, WNOHANG);// checks if any process has completed, returns immediately with 0 if none have
	if (bgPid > 0){ // when this value is greater than 0, then a process has completed
		if (WIFEXITED(status)){
			printf("background pid %d is done: exit value %d\n", bgPid, WEXITSTATUS(status));
			fflush(stdout);
		}else if (WIFSIGNALED(status)){
			printf("background pid %d is done: terminated by signal %d\n", bgPid, WTERMSIG(status));
			fflush(stdout);
		}
	}
}
// This function checks to see if the user has specifically typed in exit, cd, or status for errors such as extra arguments entered,
// or if the directory/file specified doesn't exist, before calling fork and executing the command specified.
// This function also ignores comments and blank lines being typed into the console.
// The shell must kill any other processes/jobs that the shell has started before it the program terminates.
void checkCommands(char** args, cmdFlags *cmd){
	if (cmd->numArgs == 0 || args[0] == NULL || strncmp(args[0], "#", 1) == 0){
		cmd->exitShellFlag = false; // set to false to prompt again for input
	}
	else if (strcmp(args[0], "exit") == 0){ // was the exit command entered?
		if (cmd->numArgs > 2){ // were extra arguments included with the exit command?
			printf("Too many arguments entered.\n");
			fflush(stdout);
		}else{ // exit command has been used properly
			cmd->exitShellFlag = true;
			int i; 
			for (i = 0; i < cmd->numProcesses; i++){
				kill(cmd->processes[cmd->numProcesses], SIGTERM); // kill all background processes before exiting.
			}
		}
	}
	else if (strcmp(args[0], "cd") == 0){ // was the cd command entered?
		if (cmd->numArgs > 2){ // were extra arguments included with the cd command?
			printf("Too many arguments entered.\n");
		}
		if (args[1]){ // was a directory provided to cd into?
			if (chdir(args[1]) != 0){ 
				fprintf(stderr, "%s: no such file or directory\n", args[1]);
			}
		}else{
			chdir(getenv("HOME"));
		}
	}else if (strcmp(args[0], "status") == 0){ // was the status command entered?
		fprintf(stdout, "%s\n", exitStatus);
		fflush(stdout);
	}else{ // execute command
		pid_t spawnPid;
		spawnPid = fork();

		if (spawnPid == 0){	// child process
			if (!cmd->bgProcess){	// is there no processes running in the background?
				sigaction(SIGINT, &sig_dfl, NULL); // set up signal to interrupt any foreground processes with ctrl + c
			}
			executeCommand(args, cmd);
		}else if (spawnPid == -1){ // did the fork fail?
			perror("fork error");
			exit(EXIT_FAILURE);
		}else{ // parent process
			if (cmd->bgProcess && !fg){ // background process
				cmd->processes[cmd->numProcesses++] = spawnPid;
				printf("background pid is %d\n", spawnPid);
				fflush(stdout);
			}else{ // foreground process
				getFgStatus(spawnPid, exitStatus);
			}
		}
	}
}
// Function helper to set the variables of the cmdFlags struct
void setCmdVariables(cmdFlags *cmd){
	cmd->redirStdin = false;	// reset flag for stdin redirection
	cmd->redirStdout = false;	// reset flag for stdout redirection
	cmd->numArgs = 0;			// reset number of args to 0 before processing more input
	cmd->bgProcess = false;	    // reset flag for background processes
	cmd->numProcesses = 0;      // reset numProcesses to 0
}
// Function helper to set the signal handlers up
void setSigHandlers(){
	sig_dfl.sa_handler = SIG_DFL; 
	sig_ign.sa_handler = SIG_IGN; 
	sig_stp.sa_flags = SA_RESTART;
	sig_stp.sa_handler = sigstp_handler;
	sigfillset(&sig_stp.sa_mask);
	sigaction(SIGINT, &sig_ign, NULL);
	sigaction(SIGTSTP, &sig_stp, NULL);
}