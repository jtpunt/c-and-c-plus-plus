/*
 * circular_impl.hpp
 *
 *  Created on: Feb 22, 2018
 *  	Project: CS 325 Traveling Salesman Problem
 *      Author: Jonathan Perry, David Ramirez, Armand Reitz
 */
#include <iostream>
#include <assert.h>
using std::cout;
/*****************************************************************
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 * post:  frontSentinel/backSentinel are allocated and list->size
 *        equals 0.
 ****************************************************************/
template<typename T>
CircularList<T>::CircularList(){
	frontSentinel = new Link(nullptr);
	backSentinel = new Link(nullptr);
	frontSentinel->next = frontSentinel->prev = backSentinel;
	backSentinel->next = backSentinel->prev = frontSentinel;
	size = 0;
}
/*****************************************************************
 * Overloaded constructor which allocates the list's sentinel,
 * sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 * param: value - the value to add to the new Link structure.
 * post:  frontSentinel/backSentinel are allocated and list->size
 *        equals 0.
 * post:  New link containing the value is added after the frontSentinel.
 ****************************************************************/
template<typename T>
CircularList<T>::CircularList(T value){
	frontSentinel = new Link(nullptr);
	backSentinel = new Link(nullptr);
	frontSentinel->next = frontSentinel->prev = backSentinel;
	backSentinel->next = backSentinel->prev = frontSentinel;
	addLinkAfter(frontSentinel, value);
}
/*****************************************************************
 * Overloaded constructor which allocates the list's sentinel,
 * sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 * ret: Returns the current size of the linked list structure.
 ****************************************************************/
template<typename T>
int CircularList<T>::getSize(){
	return size;
}
/*****************************************************************
 * Deallocates every link in the list and frees the list pointer.
 * pre:	  list is not empty.
 * post:  All links and the frontSentinel/backSentinel in the list
 *        are deallocated.
 ****************************************************************/
template <typename T>
void CircularList<T>::circularListDestroy(){
	while(!isEmpty()){
		removeLink(frontSentinel->next);
	}
	delete frontSentinel;
	delete backSentinel;
}
/*****************************************************************
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 * param:   link  - pointer to the link structure
 * param:   value - the value to add to the new Link structure
 * post:    newLink is added into the deque after link
 * post:	size is increased by 1
 ****************************************************************/
template <typename T>
void CircularList<T>::addLinkAfter(Link* link, T value){
	Link *newLink = new Link(value);
	newLink->next = link->next;
	newLink->prev = link;
	link->next = newLink;
	newLink->next->prev = newLink;
	size++;
}
/*****************************************************************
 * Removes the given link from the list and
 * decrements the list's size.
 * param:   link - pointer to the link structure.
 * pre:     list is not empty.
 * post:    the link is removed from the deque.
 * post:	size is decreased by 1.
 ****************************************************************/
template <typename T>
void CircularList<T>::removeLink(Link* link){
	assert(!isEmpty());
	link->prev->next = link->next;
	link->next->prev = link->prev;
	delete link;
	size--;
}
/*****************************************************************
 * Adds a new link with the given value to the front of the deque.
 * param:   value - the value to add to the new Link structure
 * pre:     list is not null
 * post:    new link with value is added to the front of the deque
 ****************************************************************/
template <typename T>
void CircularList<T>::addFront(T value){
	addLinkAfter(frontSentinel, value);
}
/*****************************************************************
 * Adds a new link with the given value to the back of the deque.
 * param:   list    pointer to the CircularList (deque)
 * param:   value   the value to add to the new Link structure
 * pre:     list is not null
 * post:    new link with value is added to the back of the deque
 ****************************************************************/
template <typename T>
void CircularList<T>::addBack(T value){
	addLinkAfter(backSentinel->prev, value);
}
/*****************************************************************
 * Returns the value of the link at the front of the deque.
 * pre:     list is not empty
 * ret:     value at the front of the deque
 ****************************************************************/
template <typename T>
typename CircularList<T>::Link* CircularList<T>::getFront(){
	return frontSentinel->next;
}
/*****************************************************************
 * Returns the value of the link at the back of the deque.
 * pre:     list is not empty
 * ret:     value at the back of the deque
 ****************************************************************/
template <typename T>
typename CircularList<T>::Link* CircularList<T>::getBack(){
	assert(!isEmpty());
	return backSentinel->prev;
}
/*****************************************************************
 * Removes the link at the front of the deque.
 * pre:     list is not empty
 * post:    link at the front of the deque is removed
 * post:    size is decreased by 1
 ****************************************************************/
template <typename T>
void CircularList<T>::removeFront(){
	assert(!isEmpty());
	removeLink(frontSentinel->next);
}
/*****************************************************************
 * Removes the link at the back of the deque.
 * pre:     list is not empty
 * post:    link at the back of the deque is removed
 * post:    size is decreased by 1
 ****************************************************************/
template <typename T>
void CircularList<T>::removeBack(){
	assert(!isEmpty());
	removeLink(backSentinel->prev);
}
/*****************************************************************
 * Returns 1 if the deque is empty and 0 otherwise.
 * ret:     1 if the deque is empty and 0 otherwise.
 ****************************************************************/
template <typename T>
bool CircularList<T>::isEmpty(){
	return size == 0;
}
/*****************************************************************
 * Prints the values of the links in the deque from front to back.
 * pre:     list is not empty
 * post:    all link's values are printed to the screen
 ****************************************************************/
template <typename T>
void CircularList<T>::print(){
	assert(!isEmpty());
	Link *myLink = frontSentinel->next;
	while (myLink != backSentinel){
		cout << myLink->value->city_id << " ";
		cout << myLink->value->x_coord << " ";
		cout << myLink->value->y_coord << "\n";
		myLink = myLink->next;
	}
	cout << size << "\n";
	cout << "\n";
}
/*****************************************************************
 * Reverses the deque.
 * pre:     list is not empty
 * post:    the deque list is reversed
 ****************************************************************/
template <typename T>
void CircularList<T>::reverse(){
	assert(!isEmpty());
	Link *reverse = frontSentinel;
	Link *forward = frontSentinel->next;
	for (int i = 0; i <= size; i++){
		reverse->next = reverse->prev;
		reverse->prev = forward;
		reverse = forward;
		forward = forward->next;
	}
}
