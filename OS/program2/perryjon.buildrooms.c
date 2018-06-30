/* CS 344 - Operating Systems
 * Program 2 - Adventure
 * Jonathan Perry
 * May 9th, 2018
 */
#include <assert.h> /* assert */
#include <dirent.h>
#include <sys/types.h> /* pid_t */
#include <sys/stat.h> /* mkdir */ 
#include <stdbool.h> 
#include <stdlib.h>
#include <string.h> /* strcpy, strcat */
#include <stdio.h>
#include <unistd.h>
#define MIN_CONNECTIONS  3
#define MAX_CONNECTIONS  6
#define MAX_ROOMS 		 7
#define MAX_ROOM_NAMES  10
#define MAX_NAME_LENGTH  8

typedef struct Room{
    int numOutboundConnections;
    struct Room* connections[MAX_CONNECTIONS];
    char name[MAX_NAME_LENGTH + 1]; /* Each room has a max of 8 characters + null terminator */
    char type[11];
} Room;

/* FUNCTION PROTOTYPES */
Room** newRoomsArr();
void freeRoomsArr(Room**);
char** newNamesArr();
void freeNamesArr(char **);
char** newTypesArr();
void freeTypesArr();
bool IsGraphFull(Room**);
void AddRandomConnection(Room**);
int GetRandomIdx(int, int);
bool CanAddConnectionFrom(Room *);
bool ConnectionAlreadyExists(Room *, Room *);
void ConnectRoom(Room *, Room *);
bool IsSameRoom(Room *, Room *);
char* popName(char **, int *, int);
char* popType( char **, int *, int);
char* getRandomName(char **, int *);
char* getRandomType();
void assignNames(Room **, char **, int *);
void assignTypes(Room **, char **, int *);
void writeFiles(Room**, char *);
char* createDirectory(char*, int);

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
        /* Each array element -  points to memory Allocated for each Room struct */
        roomsArr[i] = calloc(1, sizeof(Room));
    }
    return roomsArr;
}
/*************************************************************************
 * This function receives a pointer to the array of Room structures
 * to deallocate the memory allocated for each Room and the array itself.
 ************************************************************************/
void freeRoomsArr(Room** rooms){
	int i;
	for(i = 0; i < MAX_ROOMS; i++){
        free(rooms[i]);
	}
    free(rooms);
}
/*************************************************************************************
 * This function allocates memory for an array to hold 10 pointers to c strings,
 * and allocates memory at each index of the array to hold each c string - where each room
 * name has a max of 8 (8 + \0) characters. Calloc is used instead of using malloc/memset 
 * consecutively to zero-initialize the memory. Finally, a pointer to this memory is returned.
 *****************************************************************************************/
char ** newNamesArr(){
    char ** namesArr = calloc(MAX_ROOM_NAMES, sizeof(char*));
    assert(namesArr != 0);
    int i;
    for(i = 0; i < MAX_ROOM_NAMES; i++){
        namesArr[i] = calloc(MAX_NAME_LENGTH+1, sizeof(char));
    }
    strcpy(namesArr[0], "Bathroom");
    strcpy(namesArr[1], "Bedroom");
    strcpy(namesArr[2], "Cellar");
    strcpy(namesArr[3], "Kitchen");
    strcpy(namesArr[4], "Attic");
    strcpy(namesArr[5], "Basement");
    strcpy(namesArr[6], "Closet");
    strcpy(namesArr[7], "Office");
    strcpy(namesArr[8], "Hallway");
    strcpy(namesArr[9], "Garage");
    return namesArr;
}
/*************************************************************************
 * This function receives a pointer to the array of c strings to deallocate
 * the memory allocated for each c string and the array itself.
 ************************************************************************/
void freeNamesArr(char **namesArr){
    int i;
    for(i = 0; i < MAX_ROOM_NAMES; i++){
        free(namesArr[i]);
    }
    free(namesArr);
}
/*************************************************************************************
 * This function allocates memory for an array to hold 3 pointers to c strings,
 * and allocates memory at each index of the array to hold each c string - where each room
 * type has a max of 8-10 (8 or 10 + \0) characters. Calloc is used instead of using malloc/memset 
 * consecutively to zero-initialize the memory. Finally, a pointer to this memory is returned.
 *****************************************************************************************/
char** newTypesArr(){
    char ** typesArr = calloc(3, sizeof(char*));
    typesArr[0] = calloc(11, sizeof(char));
    typesArr[1] = calloc(9, sizeof(char));
    typesArr[2] = calloc(9, sizeof(char));
    strcpy(typesArr[0], "START_ROOM");
    strcpy(typesArr[1], "MID_ROOM");
    strcpy(typesArr[2], "END_ROOM");
    return typesArr;
}
/*************************************************************************
 * This function receives a pointer to the array of c strings to deallocate
 * the memory allocated for each c string and the array itself.
 ************************************************************************/
void freeTypesArr(char **typesArr){
    int i;
    for(i = 0; i < 3; i++){
        free(typesArr[i]);
    }
    free(typesArr);
}
/*************************************************************************
 * This function returns true if all rooms have 3 to 6 outbound connections,
 * false otherwise.
 ************************************************************************/
/* Returns true if all rooms have 3 to 6 outbound connections, false otherwise */
bool IsGraphFull(Room** roomsArr){
    int i;
    for(i = 0; i < MAX_ROOMS; i++){
        if(roomsArr[i]->numOutboundConnections < 3){
            return false;
        }
    }
    return true;
}
/*************************************************************************
 * This function Adds a random, valid outbound connection from a Room to 
 * another Room. 2 connection are added at a time (forwards and backwards)
 * to randomly chosen endpoints, until the graph satisfies the requirements.
 *      - Randomly chosen rooms must have < 6 connections
 *      - Randomly chosen rooms must not be the same rooms
 *      - Randomly chosen rooms must have not an already existing connection
 ************************************************************************/
void AddRandomConnection(Room** roomsArr){
    int A; /* holds the idx of room - which is a random number from 0 to MAX_ROOMS (7) */
    int B; /* holds the idx of room - which is a random number from 0 to MAX_ROOMS (7) */
  	while(true){ /* Loops until a room that does not have the max # of connections is found */
    	A = GetRandomIdx(0, MAX_ROOMS);
        /* Does the room at idx A already have the max # of connections? */
    	if (CanAddConnectionFrom(roomsArr[A]) == true){
      		break; /* the room at idx A does not have the max # of connections */
        }
  	}
  	do{
    	B = GetRandomIdx(0, MAX_ROOMS);
  	}while(CanAddConnectionFrom(roomsArr[B]) == false || IsSameRoom(roomsArr[A], roomsArr[B]) == true || ConnectionAlreadyExists(roomsArr[A], roomsArr[B]) == true);

  	ConnectRoom(roomsArr[A], roomsArr[B]); /* connects room A to room B, then connects room B to room A */
  	
}
/*************************************************************************
 * Returns a random Room within the range of the passed-in arguments, low/high.
 *************************************************************************/
int GetRandomIdx(int low, int high){
    return low + rand() % high;
}
/*************************************************************************
* Returns true if a connection can be added from Room x (< 6 outbound connections), 
* false otherwise
**************************************************************************/
bool CanAddConnectionFrom(Room *x){
    return x->numOutboundConnections < 6;
}
/*************************************************************************
 * Returns true if a connection from Room x to Room y already exists, 
 * false otherwise.  
 **************************************************************************/
bool ConnectionAlreadyExists(Room *x, Room *y){
    int i;
    for(i = 0; i < MAX_CONNECTIONS; i++){
        if(x->connections[i] == y){
            return true;
        }
    }
    return false;
}
/****************************************************************************
* Connects Rooms x and y together, and increments each Room's counter member
* variable by 1 to keep track of how many outbound connections the Room has. 
*****************************************************************************/
void ConnectRoom(Room *x, Room *y){
    x->connections[x->numOutboundConnections++] = y;
    y->connections[y->numOutboundConnections++] = x;
}
/****************************************************************************
* Returns true if Rooms x and y are the same Room, false otherwise.
*****************************************************************************/
bool IsSameRoom(Room *x, Room *y){
    return x == y;
}
/****************************************************************************
 * This function returns a pointer to the name that will be assigned to the 
 * next room. Because names can only be used once, the name at idx is overwritten
 * by sliding all elements to the right of idx 1 over to the left. There are 10 
 * total names in the list, but only 7 need to be used. So, decrease size by 1 
 * each time a name is removed from the list in order to return a valid, random idx.
 ****************************************************************************/
char* popName(char **namesArr, int *size, int idx){
    int i;
    char *rtnRoom = malloc(sizeof(char) * MAX_NAME_LENGTH + 1);
    strcpy(rtnRoom, namesArr[idx]);
    /* size - 1 so we don't go out of bounds of the array */
    for(i = idx; i < *size - 1; i++){
        strcpy(namesArr[i], namesArr[i+1]);
    }
    *size -= 1; /* Decrease by 1 to return a valid, random idx */
    return rtnRoom;
}
/****************************************************************************
 * This function returns a pointer to the type that will be assigned to the 
 * next room. Because the START_ROOM/END_ROOM Room types can only be used once, 
 * the type at idx is overwritten by sliding all elements to the right of idx 1 over to the left. 
 * This only occurs when the type at idx is START_ROOM/END_ROOM and not MID_ROOM.
 * When the type is MID_ROOM, MID_ROOM is not overwritten in typesArr as it's still
 * needed to finish assigning types. There are 3 total types in the list, but only 
 * 7 need to be used. So, decrease size by 1 each time a type is removed from the 
 * list (when START_ROOM/END_ROOM is encountered) in order to return a valid, random idx.
 * This ensures that 1 room is assigned START_ROOM, 1 room is assigned END_ROOM,
 * while the rest of the rooms are assigned MID_ROOM.
 ****************************************************************************/
char* popType(char **typesArr, int *size, int idx){
    int i;
    char *rtnType = malloc(sizeof(char) * 11);
    if(*size == 1){ /* MIDROOMS is all that's left */
        strcpy(rtnType, typesArr[0]);
    }else{ /* Possible room types are START_ROOM, MID_ROOM, END_ROOM */
        strcpy(rtnType, typesArr[idx]);
        /* if the room type is not MID_ROOM, then we should remove START_ROOM/END_ROOM
           from the array by sliding array elements to the left to overwrite the value
           at idx, as you can only have 1 START_ROOM/END_ROOM. */
        if(strcmp(typesArr[idx], "MID_ROOM") != 0){
            for(i = idx; i < *size - 1; i++){ 
                strcpy(typesArr[i], typesArr[i+1]);
            }
            *size -= 1; /* Decrease by 1 to return a valid, random idx */
        }
    }
    return rtnType;
}
/****************************************************************************
 * This function returns a random name by calling popName to return a random
 * name from 0 to *size (the # of elements left in namesArr) from namesArr.
 ****************************************************************************/
char* getRandomName(char **namesArr, int *size){
    return popName(namesArr, size, GetRandomIdx(0, *size));
}
/****************************************************************************
 * This function returns a random type by calling popType to return a random
 * type from 0 to *size (the # of elements left in typesArr) from typesArr.
 ****************************************************************************/
char* getRandomType(char **typesArr, int *size){
    return popType(typesArr, size, GetRandomIdx(0, *size));
}
/****************************************************************************
 * This function assigns a random name pulled from a list of 10 names to each
 * of the 7 rooms in roomsArr.
 ****************************************************************************/
void assignNames(Room **rooms, char **namesArr, int *size){
    int i;
    for(i = 0; i < MAX_ROOMS; i++){
        char *rtnRoom = getRandomName(namesArr, size);
        strcpy(rooms[i]->name, rtnRoom);
        free(rtnRoom);
    }
}
/****************************************************************************
 * This function assigns a random TYPE (START_ROOM, MID_ROOM, or END_ROOM) to
 * each of the 7 rooms in roomsArr.
 ****************************************************************************/
void assignTypes(Room **roomsArr, char ** typesArr, int *size){
    int i;
    for(i = 0; i < MAX_ROOMS; i++){
        char *rtnType = getRandomType(typesArr, size);
        strcpy(roomsArr[i]->type, rtnType);
        free(rtnType);
    }
}
/****************************************************************************
 * This function writes the contents of each Room structure stored in roomsArr
 * to their own file into the subdirectory that was sent in as an argument.
 ****************************************************************************/
void writeFiles(Room** roomsArr, char *directory){
    /* Should create files in a director called perryjon.rooms.<process_id> */
    FILE *fp;
    int i, j;
    char finalDir[55];
    memset(finalDir, '\0', 55);

    strcat(finalDir, "./"); /* current working directory ./ */
    strcat(finalDir, directory); /* perryjon.rooms.processid */
    strcat(finalDir, "/"); /* append a / to the end */

    for(i = 0; i < MAX_ROOMS; i++){
        char cur[55];
        memset(cur, '\0', 55); /* will hold finalDir + roomname */
        strcpy(cur, finalDir); /* cur == finalDir */
        strcat(cur, roomsArr[i]->name); /* ./perryjon.rooms.processid/roomName */
        fp = fopen(cur, "w");
        fprintf(fp, "ROOM NAME: %s\n", roomsArr[i]->name);
        for(j = 0; j < roomsArr[i]->numOutboundConnections; j++){
            fprintf(fp, "CONNECTION %d: %s\n", j+1, roomsArr[i]->connections[j]->name);
        }
        fprintf(fp, "ROOM TYPE: %s\n\n", roomsArr[i]->type);
        fclose(fp);
    }
}
/****************************************************************************
 * Creates a subdirectory with the process ID of the calling process appended 
 * to prefix "perryjon.rooms" in the current directory of the running program.
 ****************************************************************************/
char* createDirectory(char *directory, int process_id){
    sprintf(directory, "%s%d", "perryjon.rooms.", process_id);
    mkdir(directory, 0700);
    return directory;
}
int main(){
    srand((unsigned)time(NULL));
    char *directory = malloc(sizeof(char) * 25);
    memset(directory, '\0', 20);
    char **namesArr = newNamesArr();
    Room **roomsArr = newRoomsArr(); /* initialize Rooms Array of size 7 */
    char **typesArr = newTypesArr();
    int *namesSize = malloc(sizeof(int));
    int *typesSize = malloc(sizeof(int));
    *namesSize = MAX_ROOM_NAMES;
    *typesSize = 3;
    assignNames(roomsArr, namesArr, namesSize);
    assignTypes(roomsArr, typesArr, typesSize);
    

    while (IsGraphFull(roomsArr) == false){
        AddRandomConnection(roomsArr);
    }

    directory = createDirectory(directory, getpid());

    writeFiles(roomsArr, directory);
    freeNamesArr(namesArr);
    freeRoomsArr(roomsArr);
    freeTypesArr(typesArr);
    free(namesSize);
    free(typesSize);
    free(directory);
}