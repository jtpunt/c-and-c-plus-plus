/*
 * CS 261 Data Structures
 * Assignment 6
 * Name: Jonathan Perry
 * Date: 08/14/2017
 */
#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// CITATION: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
    char *myWord = nextWord(file);
	while(myWord != NULL)
	{
		// hashMapPut will overwrite and prevent duplicates
	    hashMapPut(map, myWord, 1); // Store the new word in the hash map
		free(myWord);
		myWord = nextWord(file);
	}
}
/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
// CITATION: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
int levenshtein(char *s1, char *s2)
{
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++)
    {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++)
        {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}
int main(int argc, const char** argv)
{
    // FIXME: implement
	int idx,  distance;
	idx = distance = 0;
	//int** myMatrix;
	HashLink* currentLink = NULL;
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        // Implement the spell checker code here..
        if(!hashMapContainsKey(map, inputBuffer)) // Does the word not exist in the dictionary?
        {
        	idx = HASH_FUNCTION(inputBuffer) % hashMapCapacity(map); // Hash word to find bucket where similar words may be found
        	if(idx < 0) idx += hashMapCapacity(map);
        	currentLink = map->table[idx]; // Point to the first link in the bucket that contains similar words
        	printf("Did you mean...?\n");
        	while(currentLink)
        	{
        		distance = levenshtein(inputBuffer, currentLink->key);
        		if(distance <= 3)
        		{
        			printf("%s %d\n", currentLink->key, distance);
        		}
        		currentLink = currentLink->next;
        	}
        }

        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}
