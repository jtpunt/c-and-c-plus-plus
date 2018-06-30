#include <assert.h> /* assert */
#include <dirent.h>
#include <sys/types.h> /* pid_t */
#include <sys/stat.h> /* mkdir */ 
#include <stdbool.h> 
#include <stdlib.h>
#include <string.h> /* strcpy, strcat */
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define MAX_CHARS 26
int getNumRepr(char letter){
	int num;
	if (letter >= 'A' && letter <= 'Z'){
  		num = letter - 'A';
	}
	else if (letter >= 'a' && letter <= 'z'){
 		num = letter - 'a';
	}
 	else{
 		num = 26;
 	}
 	return num;
}
char getCharRepr(int num){
	char space = ' ';
	if(num >= 0 && num <= 26){
		char ch = num + 65;
		return ch;
	}
	else{
		return space;
	}
}
char** genKeyTable(){
	char** keyArr = (char**)calloc(MAX_CHARS, sizeof(char*)); // malloc memory for 27 char pointers
    assert(keyArr != 0);
    int i;
    for(i = 0; i < MAX_CHARS; i++){
    	keyArr[i] = (char*)calloc(1, sizeof(char));
    }
    return keyArr;
}
void freeKeyTable(char **keyTable){
	int i;
	for(i = 0; i < MAX_CHARS; i++){
		free(keyTable[i]);
	}
	free(keyTable);
}
void fillKeyTable(char** keyTable){
	bool charUsed[26] = { false };
	int i;
	for(i = 0; i < MAX_CHARS; i++){
		bool result = false;
		do{
			int idx = 0 + rand() % 26;
			if(!charUsed[idx]){ // the char has already been used, try again
				*keyTable[i] = getCharRepr(idx);
				charUsed[idx] = true;
				result = true;
			}
		}while(!result);
	}
}
void printKeyTable(char** keyTable){
	int i;
	for(i = 0; i < MAX_CHARS; i++){
		printf("%d: %s\n", i, keyTable[i]);
	}
	printf("\n");
}
char* encryptMsg(char** keyTable, char* ciphertext, int length){
	char* encryptedMsg = (char*)calloc(length, sizeof(char));
	assert(encryptedMsg != 0);
	int i;
	for(i = 0; i < length; i++){
		int idx = getNumRepr(ciphertext[i]);
		int pos = (idx + getNumRepr(*keyTable[idx])) % MAX_CHARS;
		encryptedMsg[i] = getCharRepr(pos);
		printf("%c", ciphertext[i])
	}
	return encryptedMsg;
}
char* decryptMsg(char** keyTable, char* encryptedMsg, int length){
	char* decryptedMsg = (char*)calloc(length, sizeof(char));
	assert(decryptedMsg != 0);
	int i;
	for(i = 0; i < length; i++){
		int cipherIdx = getNumRepr(encryptedMsg[i]);
		int keyIdx = getNumRepr(*keyTable[cipherIdx]);
		int decodedIdx = cipherIdx - keyIdx % MAX_CHARS;
		encryptedMsg[i] = getCharRepr(cipherIdx);
		printf("idx: %d getNumRepr: %d subtraction: %d Modulu: %d\n", cipherIdx, keyIdx, cipherIdx - keyIdx, decodedIdx);
		// printf("%c\n", encryptedMsg[i]);
	}
	return decryptedMsg;
}
int main(){
	srand((unsigned)time(NULL));
	char *ciphertext = (char*)"Hello";
	char ch = 'A';
	char** keyTable = NULL; 
	keyTable = genKeyTable();
	fillKeyTable(keyTable);
	printKeyTable(keyTable);

	char *encryptedMsg = encryptMsg(keyTable, ciphertext, 5);
	printf("%s\n", encryptedMsg);
	// int i;
	// for(i = 0; i < 5; i++){
	// 	printf("%d %c\n", numericVal1[i], getCharRepr(numericVal1[i]));
	// }
	// printf("\n");
	// for(i = 0; i < 5; i++){
	// 	printf("%d %c\n", numericVal2[i], getCharRepr(numericVal2[i]));
	// }
	// printf("\n");
	// finalEncrypt(numericVal1, numericVal2, 5);
	char *decryptedMsg = decryptMsg(keyTable, encryptedMsg, 5);
	printf("%s\n", decryptedMsg);
	free(encryptedMsg);
	free(decryptedMsg);
	freeKeyTable(keyTable);
}