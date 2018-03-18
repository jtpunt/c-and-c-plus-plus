/*********************************************************************
** Author: Jonathan Perry
** Date: 5/07/2017
** Description: This file contains the class specification of the
** variables and functions needed for adding/deleting nodes to the head of
** list, adding/deleting nodes at the tail of the list, displaying the
** contents of the list, and displaying the contents of the list in
** reverse order.
*********************************************************************/
#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include "Creature.hpp"
#include <memory>
class LinkedList
{
protected:
	struct ListNode
	{
		int value;
		ListNode* next;
		std::shared_ptr<Creature> creature;
		ListNode(std::shared_ptr<Creature> creature1, ListNode* next1 = nullptr)
		{
			creature = creature1;
			next = next1;
		}
	};
	ListNode *head;
public:
	LinkedList();
	~LinkedList();
	void addHead(std::shared_ptr<Creature>);
	void addTail(std::shared_ptr<Creature>);
	void removeHead();
	void removeTail();
	void displayList() const;
	void reverseList();
	void traverseList(ListNode*);
};

#endif // !#LINKEDLIST_HPP