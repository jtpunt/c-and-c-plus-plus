/*********************************************************************
** Author: Jonathan Perry
** Date: 5/07/2017
** Description: This file contains the class specification of the
** variables and functions needed for displaying options to the user for
** adding/deleting nodes to the head of list, adding/deleting nodes at 
** the tail of the list, displaying the contents of the list, and displaying 
** the contents of the list in reverse order.
*********************************************************************/
#ifndef MENU_HPP
#define MENU_HPP
#include "LinkedList.hpp"
class Menu
{
private:
	LinkedList list;
public:
	Menu();
	void correctInput();
	void displayMenu();
};
#endif // !#MENU_HPP

