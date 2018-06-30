// 1. This program createa a key file of specified length.
// 2. The characters in the file generated will be any of the 27 allowd characters, generated using the standard UNIX
//    randomized methods.
// 3. Do not create spaces every 5 characters, as has been historically done.
// 4. Note that you specifically do not have to do any fancy random number generation: we're not looking for crpytographically 
//    secure random number generator! rand() is just fine.
// 5. The last character keygen outputs should be a newline.
// 6. All error text must be output to stderr, if any.
// The syntax for keygen is as follows: keygen keylength
// 	 - where keylength is the length of the key file in characters.
//   - keygen outputs to stdout
//   - Here is an example run, which redirects stdout to a key file of 256 characters called "mykey"
//   - (note that mykey is 257 characters long because of the newline): keygen 256 > mykey
#include <assert.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX_CHARS 27
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
	if(num >= 0 && num < MAX_CHARS - 1){ // all 26 characters of the alphabet
		char ch = num + 65;
		return ch;
	}
	else{ // num is a space
		return ' ';
	}
}
void printKeyTable(char** keyTable){
	int i;
	for(i = 0; i < MAX_CHARS; i++){
		printf("%d: %s\n", i, keyTable[i]);
	}
	printf("\n");
}
int modulo(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}
char* encryptMsg(char** keyTable, char* ciphertext, char* key, int length){
	char* encryptedMsg = (char*)calloc(length, sizeof(char));
	assert(encryptedMsg != 0);
	int i;
	for(i = 0; i < length; i++){
		int plaintextCharPos = getNumRepr(ciphertext[i]); // get the position of current plaintext letter in the alphabet. ETC 'A' = position 0, 'B' = position 1
		int keyCharPos = getNumRepr(*keyTable[plaintextCharPos]); // get the position of the encrypted letter in the alphabet, same as above
		key[i] = getCharRepr(keyCharPos); // assign the key char value
		// Add the position of the unencrypted letter to the position of the encrypted letter (position in the alphabet),
		// then mod 26 (The # of chars in the alphabet) to return a valid position within the alphabet
		int ciphertextCharPos = modulo(plaintextCharPos + keyCharPos, MAX_CHARS); 
		encryptedMsg[i] = getCharRepr(ciphertextCharPos); // assign the encrypted char value
		// printf("%d: %c, %d: %c, %d: %c\n", idx1, getCharRepr(idx1), idx2, getCharRepr(idx2), idx3, encryptedMsg[i]);
	}
	return encryptedMsg;
}
char* decryptMsg(char** keyTable, char* encryptedMsg, char* key, int length){
	char* decryptedMsg = (char*)calloc(length, sizeof(char));
	assert(decryptedMsg != 0);
	int i;
	for(i = 0; i < length; i++){
		int ciphertextCharPos = getNumRepr(encryptedMsg[i]); // get the position of the encrypted ciphertext letter in the alphabet
		int keyCharPos = getNumRepr(key[i]); // get the position of the current key char value
		// Subtract the position of the encrypted letter to the position of the key letter (position in the alphabet),
		// then mod 26 (The # of chars in the alphabet) to return a valid position within the alphabet
		int decryptedCharPos = modulo(ciphertextCharPos - keyCharPos, MAX_CHARS);
		decryptedMsg[i] = getCharRepr(decryptedCharPos);
	}
	return decryptedMsg;
}
void fillKeyTable(int length){
	int randChar;
	for (i = 0; i < keyLength; i++){
		randChar = 0 + rand() % MAX_CHARS; // Randomly Generates a alphabetical char or a space
		if (randChar == MAX_CHARS){		
			randChar = 32; 
		}
		fprintf(stdout, "%c", randChar);
	}

	// add trailing newline character to file
	fprintf(stdout, "\n")
}
int main(int argc, char **argv){
	// check for correct number of arguments
	if (argc != 2){
		fprintf(stderr, "Usage: %s key_length\n", argv[0]);
		exit(0);
	}

	// seed random number generator
	srand(time(NULL));


	fillKeyTable(atoi(argv[1]));

	// add trailing newline character to file
	fprintf(stdout, "\n");

	return 0;
}