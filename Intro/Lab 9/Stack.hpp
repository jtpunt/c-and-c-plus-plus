/*********************************************************************
** Author: Jonathan Perry
** Date: 6/02/2017
** Description: This file contains the class specification of the
** variables and functions needed for displaying options to the user
** so that they may push each character of a word onto the stack, and
** pop those values off the stack and into a vector that holds characters,
** so that a palindrome may be displays (a string that is the same forwards
** abd backwards).
*********************************************************************/
#ifndef STACK_HPP
#define STACK_HPP
#include <stack>
#include <vector>
class Stack
{
private:
	std::stack< char, std::vector<char> > myStack;
	// stores the characters as they're popped off of the top of the stack
	std::vector<char> myCharVector;
public:
	Stack() {};
	~Stack();
	void pushValue(char);
	void popValue();
	void displayPalindrome(int);
};
#endif // !STACK_HPP
