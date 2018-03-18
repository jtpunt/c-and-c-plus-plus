/*********************************************************************
** Author: Jonathan Perry
** Date: 6/02/2017
** Description: This file contains the class specification of the
** variables and functions needed for pushing characters to the back 
** of the queue and for removing characters from the front of the queue.
** However, these operations are only done when a random number between 
** 1 and 100 is less than a user-entered number that is also restricted 
** to 1 and 100.
*********************************************************************/
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <deque>
class Queue
{
private:
	std::deque<int> myQueue;
	double queueSum; // holds the sum of the length of the queue for each round
	double count; // Counter for the number of rounds
public:
	Queue();
	void pushToBuffer(int);
	void removeFromBuffer(int);
	int getRandomNumber(int);
	void displayBuffer();
	void resetQueue();
};
#endif // QUEUE_HPP
