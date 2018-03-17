/*
 * CS 261 Data Structures
 * Assignment 6
 * Name: Jonathan Perry
 * Date: 08/14/2017
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int HASH_FUNCTION(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

int computeIndex(HashMap *map, const char* key)
{
	assert(map != 0);
	assert(key != 0);
	int idx = HASH_FUNCTION(key) % hashMapCapacity(map);
	if(idx < 0) idx += hashMapCapacity(map);
	return idx;
}
/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    assert(link != 0);
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
	HashLink *temp, *currentLink;
	for(int i = 0; i < hashMapCapacity(map)-1; i++)
	{
		currentLink = map->table[i];
		while(currentLink) // while the buckets' link is valid
		{
			temp = currentLink; // Update pointer to the current link
			currentLink = currentLink->next; // Update pointer to the next link
			hashLinkDelete(temp); // Remove link
		}
	}
	free(map->table);
	map->capacity = map->size = 0;
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
	assert(map != 0);
	HashLink *currentLink = map->table[computeIndex(map, key)]; // Point to the first link in the correct bucket
	while(currentLink) // while the buckets' link is valid
	{
		if(!strcmp(currentLink->key, key)) // Matching key found in the current bucket?
			return &currentLink->value; // Return the address to the links' value
		currentLink = currentLink->next; // Check the next link in the bucket
	}
	return 0; // No key matches found in the bucket of links
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
	HashLink *currentLink;
	HashMap *newTable = hashMapNew(capacity); // Allocate memory for new table
    for (int i = 0; i < hashMapCapacity(map); i++) // Loop through each bucket
    {
    	currentLink = map->table[i]; // Point to the first link in the bucket
    	while(currentLink) // while the buckets' link is valid
    	{
    		// Copy values from the old table into the new resized table
    		hashMapPut(newTable, currentLink->key, currentLink->value);
    		currentLink = currentLink->next; // Update pointer to the next link
    	}
    }
    hashMapCleanUp(map);
    map->size = hashMapSize(newTable);
    map->capacity = hashMapCapacity(newTable);
    map->table = newTable->table;
    newTable->table = NULL;
    free(newTable);

}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
	HashLink* currentLink;
	int idx = computeIndex(map, key); // asserts located in computeIndex
	if (hashMapContainsKey(map, key)) // does a link with the given key already exist?
	        *hashMapGet(map, key) = value; // update the value in the link that contains the key
	else // The link with the given key was not found in the bucket
	{
		currentLink = map->table[idx]; // Point to the first link in the bucket
		map->table[idx] = hashLinkNew(key, value, currentLink); // Insert the new link at the beginning of the linked list
		map->size++;
	}
	if (hashMapTableLoad(map) >= MAX_TABLE_LOAD)
		resizeTable(map, 2 * hashMapCapacity(map));

}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    int idx = computeIndex(map, key); // map/key asserts located in computeIndex

    HashLink *currentLink, *prev;
    currentLink = prev = map->table[idx]; // Point to the first link in the bucket

    if (currentLink) // is the buckets' first link valid?
    {
    	if (!strcmp(currentLink->key, key)) // Matching key found in first link?
    		map->table[idx] = currentLink->next; // Update buckets' link pointer to it's next link
    	while(strcmp(currentLink->key, key)) // While matching key(s) are not found in the current bucket
    	{
    		prev = currentLink; // Save pointer to current link
    		currentLink = currentLink->next; // Update pointer to the next link
    	}
    	prev->next = currentLink->next; // Reconnect the links before and after currentLink
    	hashLinkDelete(currentLink); // Remove the link with the matching key
    	map->size--;
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{

	int idx = computeIndex(map, key); // map/key asserts located in computeIndex
	HashLink *currentLink = map->table[idx]; // Point to the index of the correct linkedlist bucket
	while(currentLink) // while the link is valid
	{
		if(!strcmp(currentLink->key, key)) // Matching key found in the bucket?
				return 1; // return true - matching key found
		currentLink = currentLink->next; // Update pointer to the next link
	}
	return 0; // Matching key not found
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
	assert(map != 0);
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
	assert(map != 0);
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
	int emptyBuckets = 0;
	for(int i = 0; i < hashMapCapacity(map); i++)
	{
		if(map->table[i] == NULL)
			emptyBuckets++;
	}
	return emptyBuckets;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
	return (float)hashMapSize(map)/hashMapCapacity(map);
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < hashMapCapacity(map); i++)
    {
        HashLink* link = map->table[i];
        if (link != 0)
        {
            printf("\nBucket %i ->", i);
            while (link != 0)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
