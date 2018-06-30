/* CS 344 - Operating Systems
 * Program 2 - Adventure
 * Jonathan Perry
 * May 9th, 2018
 */
#include <assert.h> /* assert */
#include <dirent.h> /* DIR */
#include <fcntl.h> /* O_RDONLY read file access permissions */
#include <pthread.h> /* pthread */
#include <sys/types.h> /* pid_t */
#include <sys/stat.h> /* mkdir */ 
#include <stdbool.h> 
#include <stdlib.h>
#include <string.h> /* strcpy, strcat */
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define NUM_THREADS      1
#define MIN_CONNECTIONS  3
#define MAX_CONNECTIONS  6
#define MAX_ROOMS        7
#define MAX_ROOM_NAMES  10
#define MAX_NAME_LENGTH  8

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

typedef struct Room{
    int numOutboundConnections;
    char connections[MAX_CONNECTIONS][MAX_NAME_LENGTH + 1];
    char name[MAX_NAME_LENGTH + 1]; /* Each room has a max of 8 characters + null terminator */
    char type[11];
} Room;

/* FUNCTION PROTOTYPES */
Room** newRoomsArr();
void freeRoomsArr(Room**);
char* getRecentFile();
char* nextWord(FILE*);
void buildRoom(FILE*, char*, Room**, int);
void readFile(char*, Room**);
void printInterface(Room*);
Room* getRoom(Room**, char*);
bool validateInput(Room*, char*);
void* getTime(void*);
void playGame(Room**);
void printPath();
Room* getStartRoom(Room**);
/*************************************************************************************
 * This function allocates memory for an array to hold 7 pointers to Room structures,
 * and allocates memory at each index of the array to hold each Room structure. Calloc is
 * used instead of using malloc/memset consecutively to zero-initialize the memory. Finally,
 * a pointer to this memory is returned.
 *****************************************************************************************/
Room** newRoomsArr(){
    /* Double pointer - points to memory allocated for an array of 7 pointers to Room structs */
    Room** roomsArr = calloc(MAX_ROOMS, sizeof(Room*));
    assert(roomsArr != 0);
    int i;
    for(i = 0; i < MAX_ROOMS; i++){
        /* Each array element - points to memory Allocated for each Room struct */
        roomsArr[i] = calloc(1, sizeof(Room));
    }
    return roomsArr;
}
/*************************************************************************
 * This function receives a pointer to the array of Room structures
 * to deallocate the memory allocated for each Room and the array itself.
 ************************************************************************/
void freeRoomsArr(Room** roomsArr){
    int i;
    for(i = 0; i < MAX_ROOMS; i++){
        free(roomsArr[i]);
    }
    free(roomsArr);
}
/************************************************************************************
 * This function looks in the current directory for the most recently created subdirectory's
 * name that matches the prefix 'perryjon.rooms'. Once this subdirectory is found, 
 * a pointer to memory allocated to hold name of the newest subdirectory is returned.
 ************************************************************************************/
char* getRecentFile(){
    int newestDirTime = -1; /* Modified timestamp of newest subdir examined */
    char targetDirPrefix[32] = "perryjon.rooms"; /* Prefix we're looking for */

    char newestDirName[256]; /* Holds the name of the newest dir that contains prefix */
    memset(newestDirName, '\0', sizeof(newestDirName));

    char *dir = malloc(sizeof(char) * 256);
    memset(dir, '\0', 256);
    DIR* dirToCheck; /* Holds the directory we're starting in */
    struct dirent *fileInDir; /* Holds the current subdir of the starting dir */
    struct stat dirAttributes; /* Holds information we've gained about subdir */

    dirToCheck = opendir("."); /* Open up the directory this program was run in */

    if (dirToCheck > 0){ /* Make sure the current directory could be opened */
        while ((fileInDir = readdir(dirToCheck)) != NULL){ /* Check each entry in dir */
            if (strstr(fileInDir->d_name, targetDirPrefix) != NULL){ /* If entry has prefix */
                stat(fileInDir->d_name, &dirAttributes); /* Get attributes of the entry */
                if ((int)dirAttributes.st_mtime > newestDirTime){ /*If this time is bigger */
                    newestDirTime = (int)dirAttributes.st_mtime;
                    memset(newestDirName, '\0', sizeof(newestDirName));
                    strcpy(newestDirName, fileInDir->d_name);
                }
            }
        }
    }
    closedir(dirToCheck); /* Close the directory we opened */
    strcpy(dir, newestDirName);
    return dir;
}
/***************************************************
 * This function returns the next word in the file.
 ***************************************************/
char* nextWord(FILE* file){
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1){
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\''){
            if (length + 1 >= maxLength){
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF){
            break;
        }
    }
    if(length == 0){
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}
/*******************************************************************************
 * This function builds each room by setting the Name, Type, and connections of the 
 * Room struct member variables from the current Room file that's being processed. 
 * If the current word being processed from the file is: 
 *  - NAME, move on to the next word, which is the name of the current Room.
 *  - CONNECTION, ignore the next word (the connection #), and move on to the
 *    next word, which is the name of the Room the current Room is connected to.
 *  - TYPE, ignore the next word in the file, which is ROOM, then move on to the 
 *    next word, which is START/MID/END. Copy START/MID/END into the current
 *    Room's member variable 'type', then concatenate an underscore and ROOM
 *    to form START_ROOM/MID_ROOM/END_ROOM.
 *******************************************************************************/
void buildRoom(FILE* myfile, char *myword, Room** roomArr, int i){
    while(myword != NULL){
        if(strcmp(myword, "NAME") == 0){
            free(myword);
            myword = nextWord(myfile);
            strcpy(roomArr[i]->name, myword);
        }else if(strcmp(myword, "CONNECTION") == 0){
            free(myword);
            free(nextWord(myfile)); /* Brings you to the connection #, which will be ignored */  
            myword = nextWord(myfile); /* Brings you to the connected room */
            strcpy(roomArr[i]->connections[roomArr[i]->numOutboundConnections++], myword);
        }
        else if(strcmp(myword, "TYPE") == 0){
            free(myword); /* Ignore TYPE */
            myword = nextWord(myfile); /* Points to the next word in the text file, which is START, MID, or END */
            free(nextWord(myfile)); /* Ignores the next word read in, which is ROOM */
            strcpy(roomArr[i]->type, myword); /* copies START, MID, OR END into the room structures member variable 'type' */
            strcat(roomArr[i]->type, "_ROOM"); /* concatenates the underscore _ROOM to START, MID, or END */
        }else{

        }
        free(myword);
        myword = nextWord(myfile);
    }
}
/********************************************************************************
 * This function looks for subdirectorys matching the prefix "perryjon.rooms"
 * and processes each Room file in the newest subdirectory found. The name, type,
 * and room connections of each file must be read back in and used to recreate
 * each Room struct. 
 ********************************************************************************/
void readFile(char* file, Room** roomArr){
    FILE *myfile;
    DIR* dirToCheck; /* Holds the directory we're starting in */
    struct dirent *fileInDir; /* Holds the current subdir of the starting dir */
    ssize_t nread;
    char readBuffer[255];
    int i = 0;
    /* See all files in the directory */
    dirToCheck = opendir(file);
    if(dirToCheck > 0){
        while ((fileInDir = readdir(dirToCheck)) != NULL){ /* Check each entry in dir */
            if(strcmp(fileInDir->d_name, ".") != 0 && strcmp(fileInDir->d_name, "..") != 0){ /* Ignore cwd and parent directory hidden files */
                char myDirectory[255];
                memset(myDirectory, '\0', 255);
                strcat(myDirectory, "./");
                strcat(myDirectory, file);
                strcat(myDirectory, "/");
                strcat(myDirectory, fileInDir->d_name);
                myfile = fopen(myDirectory, "r");

                buildRoom(myfile, nextWord(myfile), roomArr, i);
                
                fclose(myfile); /* close file before opening the next file in the subdirectory */
                i++;
            }
        }
    }else{
        printf("Something went wrong..\n");
    }
    closedir(dirToCheck);
}
/***********************************************************
 * This function prints out the name of the Room passed in,
 * along with the names of each Room it's connected to.
 ***********************************************************/
void printInterface(Room* room){
    char locations[100];
    memset(locations, '\0', 100);
    int i;
    printf("\nCURRENT LOCATION: %s\n", room->name);
    for(i = 0; i < room->numOutboundConnections; i++){
        strcat(locations, room->connections[i]);
        /* Last room connection needs a period at the end */
        if(i == room->numOutboundConnections - 1){
            strcat(locations, ".");
        }
        else{ /* Seperate room names by commas */
            strcat(locations, ", ");
        }
    }
    printf("POSSIBLE CONNECTIONS: %s\n", locations);
}
/*************************************************************
 * This function returns a pointer to a room in the roomsArr
 * whose name matches the input typed in by the user.
 *************************************************************/
Room* getRoom(Room** roomArr, char* userInput){
    int i;
    for(i = 0; i < MAX_ROOMS; i++){
        if(strcmp(roomArr[i]->name, userInput) == 0){
            return roomArr[i];
        }
    }
}
/************************************************************
 * This function compares the user input to each Room in the
 * connections character array stored in the current Room's 
 * to validate that the user entered in a valid Room name.
 ************************************************************/
bool validateInput(Room* room, char* userInput){
    int i;
    for(i = 0; i < room->numOutboundConnections; i++){
        if(strcmp(room->connections[i], userInput) == 0){
            return true;
        }
    }
    return false;
}
/*****************************************************************
 * This function writes the current time and date to a file 
 * called 'currentTime.txt' from a seperate thread. The
 * thread puts a lock on the function while it's writing, and
 * unlocks the thread when it's done. After that, the main thread
 * picks up control and reads the contents of the file and prints
 * it back out to the console.
 *****************************************************************/
void *getTime(void *vargp){
    pthread_mutex_lock(&mutex1);
    int numCharsEntered = 0;
    FILE *fp;
    struct tm *tmp;
    char MY_TIME[50];
    char str[50];
    time_t t;
    time(&t);
    tmp = localtime(&t);
    strftime(MY_TIME, sizeof(MY_TIME), "%I:%M%p %A, %B %d, %Y\n", tmp);
    fp = fopen("currentTime.txt", "w"); /* Open file for writing */
    fprintf(fp, "%s\n", MY_TIME); /* write the current time/date to the file */
    fclose(fp); /* close the file before reopening it for reading */
    pthread_mutex_unlock(&mutex1); /* Wait until the thread has completed writing to file */
    fp = fopen("currentTime.txt", "r"); /* Open file for reading */
    if( fgets (str, 60, fp)!=NULL ) {
        printf("\n");
        puts(str); /* Redirect the contents of the file to stdin */
    }
    fclose(fp); /* close the file */
}
/**********************************************************************************
 * This function starts the game, and the game continues until a room
 * with the type, "END_ROOM" is found. First, to start the game, the
 * Room with the type "START_ROOM" is retrieved. When each room is traveled to,  
 * the room's connections are printed to the screen. Then, the user types in which
 * room the user wants to travel to, and the program validates that they
 * entered a valid room name that is connected to the current Room the user
 * is at. If the user typed in a valid name, then the program finds the matching 
 * Room in roomsArr, returns that room to update the current room the user is at,
 * and increments numTries by 1 to show how many steps it took to complete the game.
 * If the user did not type in a valid name, then numTries is not incremented, and the
 * user can try to type in the room name again. If the user typed in 'time', then a 
 * seperate thread writes the time/date to a file called "currentTime.txt", and the main
 * thread reads it's contents and prints them back out to the console. Finally, each Rooms
 * on the path taken to find the 'END_ROOM' and the number of steps taken is printed out
 * to the console.
 ************************************************************************************/
void playGame(Room** roomsArr){
    pthread_t thread_id;
    int numCharsEntered = 0;
    int numTries = 0;
    size_t bufferSize = 0; /* Holds how large the allocated buffer is */
    char* lineEntered = NULL; /* Points to a buffer allocated by getline() that holds our entered string + \n + \0 */
    Room *currRoom = getStartRoom(roomsArr);
    char visitedRooms[MAX_NAME_LENGTH*2][MAX_NAME_LENGTH+1];
    while(strcmp(currRoom->type, "END_ROOM") != 0){
        printInterface(currRoom);
        printf("WHERE TO? >");
        numCharsEntered = getline(&lineEntered, &bufferSize, stdin);
        lineEntered[numCharsEntered - 1] = '\0';
        if(validateInput(currRoom, lineEntered) == true){
            currRoom = getRoom(roomsArr, lineEntered);
            strcpy(visitedRooms[numTries++], currRoom->name);
        }
        else if(strcmp(lineEntered, "time") == 0){
            pthread_create(&thread_id, NULL, getTime, NULL);
            pthread_join(thread_id, NULL);
        }
        else{
            printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
        }
    }
    free(lineEntered);
    lineEntered = NULL;
    int i;
    for(i = 0; i < numTries; i++){
        printf("%s\n", visitedRooms[i]);
    }
    printf("You have reached the END_ROOM!\n");
    printf("It took you %d steps to get to the end room.\n", numTries);
}
/***********************************************************
 * This function looks through each Room in the roomsArr to
 * return a Room that has the matching type, 'START_ROOM'.
 ***********************************************************/
Room* getStartRoom(Room** roomsArr){
    int i;
    for(i = 0; i < MAX_ROOMS; i++){
        if(strcmp(roomsArr[i]->type, "START_ROOM") == 0){
            return roomsArr[i];
        }
    }

}
int main(){
    Room **roomsArr = newRoomsArr();
    char* dir = getRecentFile();
    readFile(dir, roomsArr);
    playGame(roomsArr);
    freeRoomsArr(roomsArr);
    free(dir);
    return EXIT_SUCCESS;
}