/*********************************************************************
** Author: Jonathan Perry
** Date: 6/02/2017
** Description: This file contains the class specification of the
** variables and functions needed for displaying options to the user
** so that they may create a palindrome and to add or remove numbers 
** from a queue based on a percent chance, which is set by the user
** in this menu.
*********************************************************************/
#ifndef MENU_HPP
#define MENU_HPP
#include "Stack.hpp"
#include "Queue.hpp"
class Menu
{
private:
	Stack myStack;
	Queue myQueue;
	int roundNumbers = 0;
public:
	// Input must be between 1 and 1000
	class outOfRange{};
	Menu();
	void correctInput();
	void displayMenu();
	void queueMenu();
	void stackMenu();
	int getInput();
	bool addToBuffer();
	bool removeFromBuffer();
};
#endif // !#MENU_HPP

