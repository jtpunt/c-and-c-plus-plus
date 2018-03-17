/*****************************************************************
* CS261- Assignment 3
* Name: Jonathan Perry
* Date: 07/24/17
* Solution description: Linked List Deque Implementation
****************************************************************/
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};
/*****************************************************************
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 * param: 	list	pointer to the LinkedList structure
 * pre:	    list is not null
 * post:	list->frontSentinel is not null
 * post:	list->backSentinel is not null
 * post:    Front and Back sentinels point to each other
 * post:	Size of LinkedList structure is 0
 ****************************************************************/
static void init(struct LinkedList* list) 
{
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	list->backSentinel = malloc(sizeof(struct Link));
	assert(list->backSentinel != 0);
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->size = 0;
}
/*****************************************************************
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 * param: 	list	pointer to the LinkedList structure
 * param:   link    pointer to the Link Structure to add before
 * param:   value   the value to add to the new Link structure
 * pre:	    list is not null
 * pre:     link is not null
 * post:	newLink is not null
 * post:	Size of LinkedList structure is increased by 1
 ****************************************************************/
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(list != 0 && link != 0);
	struct Link *newLink = (struct Link*)malloc(sizeof(struct Link));
	assert(newLink != 0);
	newLink->value = value;
	newLink->prev = link->prev;
	newLink->next = link;
	link->prev->next = newLink;
	link->prev = newLink;
	list->size++;
}
/*****************************************************************
 * Removes the given link from the list and
 * decrements the list's size.
 * param: 	list	pointer to the LinkedList structure
 * param:   link    pointer to the Link Structure to remove
 * pre:	    list is not null
 * pre:     link is not null
 * post:	link is deallocated
 * post:	Size of LinkedList structure is decreased by 1
 ****************************************************************/
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != 0 && link != 0);
	link->prev->next = link->next;
	link->next->prev = link->prev;
	free(link);
	list->size--;
}
/*****************************************************************
 * Allocates and initializes a list.
 * param: 	None
 * pre:	    None
 * post:    Front and Back sentinels point to each other
 ****************************************************************/
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}
/*****************************************************************
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 * param: 	list	pointer to the LinkedList structure
 * pre:	    list is not null
 * post:	list's link structures are deallocated
 * post:    list's front and back sentinels are deallocated
 * post:	Size of LinkedList structure is decreased to 0
 ****************************************************************/
void linkedListDestroy(struct LinkedList* list)
{
	assert(list != 0);
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}
/*****************************************************************
 * Adds a new link with the given value to the front of the deque.
 * param: 	list	pointer to the LinkedList structure
 * param:   value   the value to add to the new Link structure
 * pre:	    list is not null
 * post:	Size of LinkedList structure is increased by 1
 ****************************************************************/
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
	addLinkBefore(list, list->frontSentinel->next, value);
}
/*****************************************************************
 * Adds a new link with the given value to the back of the deque.
 * param: 	list	pointer to the LinkedList structure
 * param:   value   the value to add to the new Link structure
 * pre:	    list is not null
 * post:	Size of LinkedList structure is increased by 1
 ****************************************************************/
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
	addLinkBefore(list, list->backSentinel, value);
}
/*****************************************************************
 * Returns the value of the link at the front of the deque.
 * param: 	list	pointer to the LinkedList structure
 * pre:     list is not null
 * pre:	    list is not empty
 * post:	none
 ****************************************************************/
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	return list->frontSentinel->next->value;
}
/*****************************************************************
 * Returns the value of the link at the back of the deque.
 * param: 	list	pointer to the LinkedList structure
 * pre:     list is not null
 * pre:	    list is not empty
 * post:	none
 ****************************************************************/
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	return list->backSentinel->prev->value;
}
/*****************************************************************
 * Removes the link at the front of the deque.
 * param: 	list	pointer to the LinkedList structure
 * pre:     list is not null
 * pre:	    list is not empty
 * post:	list->size is reduced by 1
 ****************************************************************/
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->frontSentinel->next);
}
/*****************************************************************
 * Removes the link at the back of the deque.
 * param: 	list	pointer to the LinkedList structure
 * pre:     list is not null
 * pre:	    list is not empty
 * post:	list->size is reduced by 1
 ****************************************************************/
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->backSentinel->prev);
}
/*****************************************************************
 * Returns 1 if the deque is empty and 0 otherwise.
 * param: 	list	pointer to the LinkedList structure
 * pre:     list is not null
 * post:	None
 ****************************************************************/
int linkedListIsEmpty(struct LinkedList* list)
{
	assert(list != 0);
	return EQ(list->size, 0);
}
/*****************************************************************
 * Prints the values of the links in the deque from front to back.
 * param: 	list	pointer to the LinkedList structure
 * pre:     list is not null
 * post:	None
 ****************************************************************/
void linkedListPrint(struct LinkedList* list)
{
	assert(list != NULL);
	struct Link *myList = list->frontSentinel->next;
	while (!EQ(myList, list->backSentinel))
	{
		printf("%d\n", myList->value);
		myList = myList->next;
	}
}
/*****************************************************************
 * Adds a link with the given value to the bag.
 * param: 	list	pointer to the bag
 * param:   value   the value to added
 * pre:     list is not null
 * post:	A new link containing the value is added to the bag
 ****************************************************************/
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
	linkedListAddBack(list, value);
}
/*****************************************************************
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 * param: 	list	pointer to the bag
 * param:   value   the value to searched for in the bag
 * pre:     list is not null
 * pre:     list is not empty
 * post:	None
 ****************************************************************/
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
	assert(!(linkedListIsEmpty(list)));
	// Create a new struct to parse the list
	// Set the struct to point to the first value in the list
	struct Link *newStruct = list->frontSentinel->next;
	// Traverse through the list until the value is found or the end is reached
	while (!EQ(newStruct, list->backSentinel))
	{
		if (EQ(newStruct->value, value))
		{
			return 1; // value found
		}
		// Traverse to the next node if the value is not found
		newStruct = newStruct->next;
	}
	//Returns false if e is not found
	return 0;
}

/*****************************************************************
 * Removes the first occurrence of a link with the given value.
 * param: 	list	pointer to the bag
 * param:   value   the value to removed from the bag
 * pre:     list is not null
 * pre:     list is not empty
 * post:	value has been removed
 * post:    list->size has been reduced by 1
 ****************************************************************/
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// Create a new struct to parse the list
	// Assure the list is not null and not empty
	assert(list != 0);
	assert(!(linkedListIsEmpty(list)));
	// Create a new struct to parse the list
	// Set the struct to point to the first value in the list
	struct Link *newStruct = list->frontSentinel->next;
	// Traverse through the list until the value is found or the end is reached
	while (!EQ(newStruct,list->backSentinel))
	{
		if (EQ(newStruct->value, value)) 
		{
			// If value is matched, the removeLink function is called and the function exits after
			removeLink(list, newStruct);
			break;
		}
		// Traverse to the next node if the value is not found
		newStruct = newStruct->next; 
	}
}
