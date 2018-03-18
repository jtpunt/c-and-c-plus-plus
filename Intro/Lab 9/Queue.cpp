/*********************************************************************
** Author: Jonathan Perry
** Date: 6/03/2017
** Description: This file contains the implementation code of the
** variables and functions needed for pushing characters to the back 
** of the queue and for removing characters from the front of the queue.
** However, these operations are only done when a random number between 
** 1 and 100 is less than a user-entered number that is also restricted 
** to 1 and 100.
*********************************************************************/
#include "Queue.hpp"
#include <iostream>
using std::cin;
using std::endl;
using std::cout;
/*********************************************************************
** Description: This is the default constructor which initializes the
** both private variables of the Queue class to 0.0.
*********************************************************************/
Queue::Queue()
{
	count = 0.0;
	queueSum = 0.0;
}
/*********************************************************************
** Description: This is a function that receives the user-specified
** percentage to use to add a random number between 1 and 1000 to the
** back of the buffer, but only when a random number rolled between
** 1 and 100 is less than the user-specified percentage that this function
** receives.
*********************************************************************/
void Queue::pushToBuffer(int percent)
{
	int randomNumber = getRandomNumber(100);
	// If the outcome of the random integer is less than the user-specified integer
	if (randomNumber < percent)
	{
		int addedNumber = getRandomNumber(1000);
		// Then push a random number between 1 and 1000 to the buffer
		myQueue.push_back(addedNumber);
		cout << "The number " << addedNumber << " has been added to the buffer." << endl;
	}
	else
	{
		cout << "No values were added to the end of the buffer." << endl;
	}
	cout << "\nThe random number is: " << randomNumber << endl;
	cout << "The user entered number is: " << percent << endl;
}
/*********************************************************************
** Description: This is a function that receives the user-specified
** percentage to use to remove a number from the front of the buffer,
** but only when a random number rolled between 1 and 100 is less than 
** the user-specified percentage that this function receives.
*********************************************************************/
void Queue::removeFromBuffer(int percent)
{
	int randomNumber = getRandomNumber(100);
	// If the outcome of the random integer is less than the user-specified integer
	if (randomNumber < percent)
	{
		// Check to see if the queue is empty before removing values
		if (!myQueue.empty())
		{
			cout << "The number " << myQueue.front() << " has been removed from the buffer." << endl;
			// Then push a random number between 1 and 1000 to the buffer
			myQueue.pop_front();
		}
		else
		{
			cout << "The queue is empty, there are no values to remove." << endl;
		}
	}
	else
	{
		cout << "No values were removed from the front of the buffer." << endl;
	}
	cout << "\nThe random number is: " << randomNumber << endl;
	cout << "The user entered number is: " << percent << endl;
}
/*********************************************************************
** Description: This is a function that returns a random number between 1 
** and 100 or 1000.
**	- 100 is the max number used to help determine the percent chance of 
**	  the random number between 1 and 1000 being added to the queue.
**  - 100 is also the max number used to help determine the percent chance
**    of the number at the front of the queue being removed.
*********************************************************************/
int Queue::getRandomNumber(int max)
{
	return rand() % max + 1;
}
/*********************************************************************
** Description: This is a function that displays all integer numbers
** stored in the queue, and the average length of the queue after each 
** completed round. 
*********************************************************************/
void Queue::displayBuffer()
{
	cout << "Front of the queue -->";
	for (auto i : myQueue)
	{
		cout << "[" << i << "]";
	}
	count++; // Increments each round
	queueSum += myQueue.size(); // adds in the length of the queue for each round
	cout << "<-- back of the queue" << endl;
	cout << "The average length of the queue is " << queueSum / count << "." << endl;
}
/*********************************************************************
** Description: This is a function which clears the queue, resets the 
** count and queueAverage to zero, so that more rounds can be played.
*********************************************************************/
void Queue::resetQueue()
{
	while (!myQueue.empty())
	{
		myQueue.pop_front();
	}
	count = 0;
	queueSum = 0;
}