/*********************************************************************
** Author: Jonathan Perry
** Date: 5/22/2017
** Description: This file contains the class specification of the
** variables and functions needed for displaying options to the user
** so that they may add nodes to the back of the queue, display the 
** value stored in the node at the front of the queue, remove the 
** node at the front of the queue, and display every value from the
** front node to the rear node, and exit.
*********************************************************************/
#ifndef MENU_HPP
#define MENU_HPP
#include "Queue.hpp"
class Menu
{
private:
	Queue myQueue;
public:
	Menu();
	void correctInput();
	void displayMenu();
};
#endif // !#MENU_HPP

