/*********************************************************************
** Author: Jonathan Perry
** Date: 5/22/2017
** Description: This file contains the class specification of the
** variables and functions needed for adding nodes to the back of the
**  queue, retrieving a member variables of the node at the front of the
** queue, removing the node at the front of the queue, displaying the 
** value of each nodes member variable known as 'value', and checking
** to see if the queue is empty.
*********************************************************************/
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <memory>
#include <vector>
#include "Creature.hpp"
class Queue
{
private:
	struct QueueNode
	{
		int value;
		QueueNode* next;
		QueueNode* prev;
		std::shared_ptr<Creature> creature;
		QueueNode(std::shared_ptr<Creature> creature1, QueueNode* next1 = nullptr, QueueNode* prev1 = nullptr)
		{
			creature = creature1;
			next = next1;
			prev = prev1;
		}
	};
	QueueNode* front; // Points to the place in the queue that used to hold the item that was last removed from the queue.
	QueueNode* rear; // Points to the place in the queue holding the itemt hat was last added to the queue
public:
	Queue();
	~Queue(); // Frees all the memory of the nodes in the queue
	void addBack(std::shared_ptr<Creature>);
	//void addBack(int); // Puts an item at the end of the queue
	std::shared_ptr<Creature> getCreature();
	void removeFront(); // Removes the front item in the structure
	bool isEmpty() const; // Returns true if the linked list is empty, false if the linked list contains values
	void displayQueue();
};
#endif // !QUEUE_HPP
