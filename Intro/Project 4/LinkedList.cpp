/*********************************************************************
** Author: Jonathan Perry
** Date: 5/07/2017
** Description: This file contains the implementation code of the
** variables and functions needed for adding/deleting nodes to the head of
** list, adding/deleting nodes at the tail of the list, displaying the
** contents of the list, and displaying the contents of the list in
** reverse order.
*********************************************************************/
#include "LinkedList.hpp"
#include <iostream>
using std::shared_ptr;
using std::cout;
using std::endl;
/*********************************************************************
** Description: This is the default constructor of the LinkedList class
** which sets the head node to nullptr.
*********************************************************************/
LinkedList::LinkedList()
{
	head = nullptr;
}
/*********************************************************************
** Description: This is the default destructor of the LinkedList class
** which deletes all nodes before the program exits.
*********************************************************************/
LinkedList::~LinkedList()
{
	ListNode* nodePtr = head;
	while (nodePtr != nullptr)
	{
		// Point to the node that'll be deleted
		ListNode *nodeToDelete = nodePtr;
		// Move on to the next node
		nodePtr = nodePtr->next;
		nodeToDelete->creature = nullptr;
		delete nodeToDelete;
	}
}
/*********************************************************************
** Description: This is a function that accepts as an argument a number
** of type double, creates a node containing the number, and adds the node
** to head.
*********************************************************************/
void LinkedList::addHead(shared_ptr<Creature>creature)
{
	ListNode *previousNodePtr;
	// Check to see if the list is currently empty
	if (head == nullptr)
	{
		// Add the new node
		head = new ListNode(creature, head);
	}
	else
	{
		// Insert the new node at the beginning
		previousNodePtr = new ListNode(creature, head);
		// Update head node pointer to the newly created node header
		head = previousNodePtr;
	}
}
/*********************************************************************
** Description: This is a function that accepts as an argument a number
** of type double, creates a node containing the number, and adds the node
** to tail. 
*********************************************************************/
void LinkedList::addTail(shared_ptr<Creature>creature)
{
	// Check to see if the list is currently empty
	if (head == nullptr)
	{
		head = new ListNode(creature);
	}
	// The list is not empty
	else
	{
		// Set the pointer 'nodePtr' to the beginning of the list
		ListNode *nodePtr = head;
		// Sort through until it's at the end of the list
		while (nodePtr->next != nullptr)
		{
			// Set the pointer to point to the last node
			nodePtr = nodePtr->next;
		}
		// Add the new node
		nodePtr->next = new ListNode(creature);
	}
}
/*********************************************************************
** Description: This is a function that removes the head node from the
** list.
*********************************************************************/
void LinkedList::removeHead()
{
	ListNode* nodePtr;

	// If the list is empty, do nothing
	if (!head)
	{
		return;
	}
	nodePtr = head;   
	// Move the head node pointer to the node to the right of it before deleting
	head = head->next;
	delete nodePtr;
}
/*********************************************************************
** Description: This is a function that removes the tail node from the
** list by sorting through the list until the function finds it's at 
** the end of the list.
*********************************************************************/
void LinkedList::removeTail()
{
	// Check to see if the list is empty
	if (!head)
	{
		return;
	}
	// Check to see if the first node is one to be deleted
	if (head->next == nullptr) 
	{
		delete head;
		head = nullptr;
	}
	else 
	{
		ListNode *nodePtr = head->next;
		ListNode *previousNodePtr = nullptr;
		while (nodePtr->next != nullptr) 
		{
			previousNodePtr = nodePtr;
			nodePtr = nodePtr->next;
		}
		previousNodePtr->next = nullptr;
		delete nodePtr;
	}
}
/*********************************************************************
** Description: This is a function that starts at the head node of the 
** list and moves all the way to tail node of the list, displaying each
** value as it passes through each node.
*********************************************************************/
void LinkedList::displayList() const
{
	ListNode* nodePtr = head;
	while (nodePtr)
	{
		cout << nodePtr->creature->getName() << " ";
		nodePtr = nodePtr->next;
	}
	cout << endl;
}
/****************************************************** ***************
** Description: This is a function that calls the function known as
** traverseList and sends it a pointer to the head of the list, so that
** traverseList may recursively display the contents in reverse order.
*********************************************************************/
void LinkedList::reverseList()
{
	traverseList(head);
}
/*********************************************************************
** Description: This is a function that recursively displays the values 
** of the list in reverse order.
*********************************************************************/
void LinkedList::traverseList(ListNode* nodePtr)
{
	if (nodePtr)
	{
		traverseList(nodePtr->next);
		cout << nodePtr->creature->getName() << " ";
	}
}