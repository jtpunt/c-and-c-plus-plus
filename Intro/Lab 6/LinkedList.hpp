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
class LinkedList
{
protected:
	struct ListNode
	{
		int value;
		ListNode* next;
		ListNode(double value1, ListNode* next1 = nullptr)
		{
			value = value1;
			next = next1;
		}
	};
	ListNode *head;
public:
	LinkedList();
	~LinkedList();
	void addHead(int);
	void addTail(int);
	void removeHead();
	void removeTail();
	void displayList() const;
	void reverseList();
	void traverseList(ListNode*);
};

#endif // !#LINKEDLIST_HPP