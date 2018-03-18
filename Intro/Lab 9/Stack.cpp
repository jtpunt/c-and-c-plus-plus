/*********************************************************************
** Author: Jonathan Perry
** Date: 5/28/2017
** Description: This file contains the implementation code of the
** variables and functions needed for displaying options to the user
** so that they may push each character of a word onto the stack, and
** pop those values off the stack and into a vector that holds characters,
** so that a palindrome may be displays (a string that is the same forwards
** abd backwards).
*********************************************************************/
#include "Stack.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::reverse;
using std::cout;
using std::cin;
using std::endl;

/*********************************************************************
** Description: This is the default destructor that removes all characters
** off of the stack. 
*********************************************************************/
Stack::~Stack()
{
	// Keep looping while the stack still contains characters
	while (!myStack.empty())
	{
		// Removes all characters stored in the stack
		popValue();
	}
}
/*********************************************************************
** Description: This is a function that receives each individual characters
** from a user-specified word and pushes them onto the stack.
*********************************************************************/
void Stack::pushValue(char ch)
{
	cout << "Pushing character \'" << ch << "\' onto the stack." << endl;
	myStack.push(ch);
}
/*********************************************************************
** Description: This is a function that (when the stack is not empty)
** displays the character to be removed from the top of the stack, 
** pushes the character into a vector of characters, and then pops that 
** character off of the top of the stack. 
*********************************************************************/
void Stack::popValue()
{
	if (!myStack.empty())
	{ 
		cout << "Popping character \'" << myStack.top() << "\' off of the stack."<< endl;
		myCharVector.push_back(myStack.top()); // Push the top of the stack into the vector
		myStack.pop(); // Remove the character from the stock
	}
	else
	{
		cout << "There are no values left to remove. ";
	}
}
/*********************************************************************
** Description: This is a function that keeps calling the popValue 
** function until the stack is empty. Each call to popValue pushes an 
** individual character of the user-specified word into a vector of 
** characters. Once the stack is empty, the vector is reversed twice
** to display the palindrome (i.e. a string that is the same forwards
** and backwords). The first reverse prints out the user-specified
** word forwards and the second reverse prints out the user-specified 
** word backwards.
*********************************************************************/
void Stack::displayPalindrome(int stringSize)
{	
	// Keep looping while the stack still contains characters
	while (!myStack.empty())
	{
		// Removes all characters stored in the stack
		popValue();
	}
	cout << "Your palindrome: ";
	// Gives us the normal user-specifed word (forwards)
	reverse(myCharVector.begin(), myCharVector.end());
	for (auto i : myCharVector)
	{
		cout << i;
	}
	// Gives us the reverse of the user-specifed word (backwards)
	reverse(myCharVector.begin(), myCharVector.end());
	for (auto i : myCharVector)
	{
		cout << i;
	}
	// Clear the vector of all character data
	myCharVector.clear();
}