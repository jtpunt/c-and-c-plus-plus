/*********************************************************************
** Author: Jonathan Perry
** Date: 5/22/2017
** Description: This file contains the implementation code of the
** variables and functions needed for adding nodes to the back of the
**  queue, retrieving a member variables of the node at the front of the
** queue, removing the node at the front of the queue, displaying the
** value of each nodes member variable known as 'value', and checking
** to see if the queue is empty.
*********************************************************************/
#include "Queue.hpp"
#include <iostream>
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::cin;
using std::endl;
/*********************************************************************
** Description: This is the default constructor of the Queue class which
** sets the front and rear points to nullptr.
*********************************************************************/
Queue::Queue()
{
	front = nullptr;
	rear = nullptr;
}
/*********************************************************************
** Description: This is the default destructor of the Queue class which
** starts at the front node and moves over 1 node at a time while deleting
** each node until it deletes the rear node.
*********************************************************************/
Queue::~Queue() // Frees all the memory of the nodes in the queue
{
	QueueNode* garbage = front;
	while (garbage != nullptr && garbage != rear)
	{
		front = front->next;
		garbage->next = nullptr;
		garbage->creature.reset();
		delete garbage;
		garbage = front;
	}
}
/********************************************\*************************
** Description: This is a function that creates a new QueueNode object
** and adds it to the queue. Before adding a new node to the queue, this
** function checks to see if the queue is empty, or already filled with
** other nodes before creating the new QueueNode object. When the queue 
** is empty, the front and rear pointers are set to this newly created
** object, but when there are nodes present in the queue, the object is
** added to the end (rear) of the queue. Finally, the rear's next node
** over is reconnected with the front node, and then the (rear) node
** preceeding the front node are reconnected to sustain the doubly-linked
** circular structure.
*********************************************************************/
void Queue::addBack(shared_ptr<Creature> creature)
{
	if (isEmpty()) // Adding first node
	{
		front = new QueueNode(creature);
		rear = front;
		rear->next = front; // rear's next node is the front node
		front->prev = rear; // front's prev node is the rear node
	}
	else // Adding n node(s)
	{
		rear->next = new QueueNode(creature); // Create the next new node
		rear = rear->next; // adjust rear pointer to the newly created node
		// Reconnect the doubly-linked structure so that the rear's next node is the front's node
		rear->next = front;
		// Reconnect the doubly-linkd structured so that the front's prev node is the rear's node
		front->prev = rear;
	}
}
/*********************************************************************
** Description: This is a member function of the Queue class that returns
** the value of the first node in the queue.
*********************************************************************/
shared_ptr<Creature> Queue::getCreature()
{
	if (isEmpty())
	{
		cout << "There are no values in the queue. " << endl;
		return nullptr;
	}
	else
	{
		return front->creature;
	}
}
/*********************************************************************
** Description: This is member function of the Queue class which removes
** the node at the front of the queue and reconnects the adjusted front
** node to the (rear) node at the end of the queue to sustain the 
** doubly-linked circular structure.
*********************************************************************/
void Queue::removeFront() 
{
	if (isEmpty()) 
	{
		cout << "The queue is empty." << endl;
	}
	// When front's next value == front's previous value, we have 1 node left in queue
	else if (front == rear)
	{
		QueueNode* temp = nullptr;
		//cout << front->creature->getName() << " has been removed from the queue." << endl;
		temp = front;
		// Set front to nullptr so that nodes may be new nodes may be added again
		front = nullptr;
		delete temp;
	}
	else
	{
		QueueNode* temp = nullptr;
		temp = front;
		front = front->next;
		// Reconnect the doubly-linkd structured so that the front's prev node is the rear's node
		front->prev = rear;
		// Reconnect the doubly-linked structure so that the rear's next node is the front's node
		rear->next = front;
		delete temp;
	}
}
/*********************************************************************
** Description: This is a member function of the Queue class which returns
** true when front is not pointing to any nodes, false when it is poining
** to some node.
*********************************************************************/
bool Queue::isEmpty() const
{
	return front == nullptr;
}
/*********************************************************************
** Description: This is a member function of the Queue class which
** displays each value from the first node in the queue to the value
** of the last node in the queue, and then displays the front value again
** when the function reapproaches it.
*********************************************************************/
void Queue::displayQueue()
{
	int front_value_repeats = 0;
	QueueNode* displayNext = front;
	while (displayNext != nullptr && front_value_repeats < 2)
	{
		if (displayNext == front)
		{
			front_value_repeats++;
		}
		cout << displayNext->creature->getName() << " ";
		displayNext = displayNext->next;
	}
	if(front != nullptr)
	{
		cout << "<-(the first node)" << endl;
	}
	else
	{
		cout << "There are no values in the queue. " << endl;
	}
}
