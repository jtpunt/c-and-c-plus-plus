/*****************************************************************
* CS261- Assignment 3 
* Name: Jonathan Perry
* Date: 07/24/7
* Solution description: Circular List Deque Implementation
****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};
/*****************************************************************
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 * param: 	list	pointer to the LinkedList structure
 * pre:	    list is not null
 * post:	list->sentinel is allocated and list->size equals 0
 ****************************************************************/
static void init(struct CircularList* list)
{
	assert(list != 0);
	list->sentinel = malloc(sizeof(struct Link));
	assert(list->sentinel != 0);
	list->sentinel->next = list->sentinel->prev = list->sentinel;
	list->size = 0;
}
/*****************************************************************
 * Creates a link with the given value and NULL next and prev pointers.
 * param:   value   the value to add to the new Link structure
 * pre:	    none
 * post:	newLink is not null
 ****************************************************************/
static struct Link* createLink(TYPE value)
{
	struct Link *newLink = malloc(sizeof(struct Link));
	assert(newLink != 0);
	newLink->prev = newLink->next = 0;
	newLink->value = value;
	return newLink;
}
/*****************************************************************
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 * param:   list    pointer to the CircularList (deque)
 * param:   link    pointer to the link structure
 * param:   value   the value to add to the new Link structure
 * pre:	    list is not null
 * pre:     link is not null
 * pre:     link is not empty
 * post:    newLink is added into the deque after link
 * post:	list->size is increased by 1
 ****************************************************************/
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != 0);
	assert(link != 0);
	//assert(!circularListIsEmpty(list));
	struct Link *newLink = createLink(value);
	newLink->next = link->next;
	newLink->prev = link;
	link->next = newLink;
	newLink->next->prev = newLink;
	list->size++;
}
/*****************************************************************
 * Removes the given link from the list and
 * decrements the list's size.
 * param:   list    pointer to the CircularList (deque)
 * param:   link    pointer to the link structure
 * pre:	    list is not null
 * pre:     list is not empty
 * post:    the link is removed from the deque
 * post:	list->size is decreased by 1
 ****************************************************************/
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	link->prev->next = link->next;
	link->next->prev = link->prev;
	free(link);
	list->size--;
}
/*****************************************************************
 * Allocates and initializes a list.
 * param:   none
 * pre:	    none
 * post:	list->sentinel is allocated and list->size equals 0
 ****************************************************************/
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}
/*****************************************************************
 * Deallocates every link in the list and frees the list pointer.
 * param:   list    pointer to the CircularList (deque)
 * pre:	    list is not null
 * post:    All links and the sentinel in the list are deallocated
 ****************************************************************/
void circularListDestroy(struct CircularList* list)
{
	assert(list != 0);
	while(!circularListIsEmpty(list))
	{
		removeLink(list, list->sentinel->next);
	}
}
/*****************************************************************
 * Adds a new link with the given value to the front of the deque.
 * param:   list    pointer to the CircularList (deque)
 * param:   value   the value to add to the new Link structure
 * pre:     list is not null
 * post:    new link with value is added to the front of the deque
 ****************************************************************/
void circularListAddFront(struct CircularList* list, TYPE value)
{
	assert(list != 0);
	addLinkAfter(list, list->sentinel, value);
}
/*****************************************************************
 * Adds a new link with the given value to the back of the deque.
 * param:   list    pointer to the CircularList (deque)
 * param:   value   the value to add to the new Link structure
 * pre:     list is not null
 * post:    new link with value is added to the back of the deque
 ****************************************************************/
void circularListAddBack(struct CircularList* list, TYPE value)
{
	assert(list != 0);
	addLinkAfter(list, list->sentinel->prev, value);
}
/*****************************************************************
 * Returns the value of the link at the front of the deque.
 * param:   list    pointer to the CircularList (deque)
 * pre:     list is not null
 * pre:     list is not empty
 * post:    none
 * ret:     value at the front of the deque
 ****************************************************************/
TYPE circularListFront(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	return list->sentinel->next->value;
}
/*****************************************************************
 * Returns the value of the link at the back of the deque.
 * param:   list    pointer to the CircularList (deque)
 * pre:     list is not null
 * pre:     list is not empty
 * post:    none
 * ret:     value at the back of the deque
 ****************************************************************/
TYPE circularListBack(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	return list->sentinel->prev->value;
}
/*****************************************************************
 * Removes the link at the front of the deque.
 * param:   list    pointer to the CircularList (deque)
 * pre:     list is not null
 * pre:     list is not empty
 * post:    link at the front of the deque is removed
 * post:    list->size is decreased by 1
 ****************************************************************/
void circularListRemoveFront(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	removeLink(list, list->sentinel->next);
}
/*****************************************************************
 * Removes the link at the back of the deque.
 * param:   list    pointer to the CircularList (deque)
 * pre:     list is not null
 * pre:     list is not empty
 * post:    link at the back of the deque is removed
 * post:    list->size is decreased by 1
 ****************************************************************/
void circularListRemoveBack(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	removeLink(list, list->sentinel->prev);
}
/*****************************************************************
 * Returns 1 if the deque is empty and 0 otherwise.
 * param:   list    pointer to the CircularList (deque)
 * pre:     list is not null
 * post:    none
 * ret:     1 if the deque is empty and 0 otherwise.
 ****************************************************************/
int circularListIsEmpty(struct CircularList* list)
{
	assert(list != 0);
	return list->size == 0;
}
/*****************************************************************
 * Prints the values of the links in the deque from front to back.
 * param:   list    pointer to the CircularList (deque)
 * pre:     list is not null
 * pre:     list is not empty
 * post:    all link's values are printed to the screen
 ****************************************************************/
void circularListPrint(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	struct Link *myLink = list->sentinel->next;
	while (myLink != list->sentinel)
	{
		printf("%g\n", myLink->value);
		myLink = myLink->next;
	}
}
/*****************************************************************
 * Reverses the deque.
 * param:   list    pointer to the CircularList (deque)
 * pre:     list is not null
 * pre:     list is not empty
 * post:    the deque list is reversed
 ****************************************************************/
void circularListReverse(struct CircularList* list)
{
	assert(list != 0);
	assert(!circularListIsEmpty(list));
	struct Link *reverse = list->sentinel;
	struct Link *forward = list->sentinel->next;
	for (int i = 0; i <= list->size; i++)
	{
		reverse->next = reverse->prev;
		reverse->prev = forward;
		reverse = forward;
		forward = forward->next;
	}
}
