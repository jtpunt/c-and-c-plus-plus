/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This header file defines the class specifications of
** variables and functions needed for creating and managing a list
** of grocery items.
*********************************************************************/
#ifndef MENU_HPP
#define MENU_HPP
#include "List.hpp"
class Menu
{
private:
	// Creates a new list
	List list;
public:
	// Constructor which calls displayMenu function
	Menu();
	void clearInput();
	void displayMenu();
};

#endif
