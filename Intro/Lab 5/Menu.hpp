/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This header file defines the class specifications of
** variables and functions needed for gathering all user-input needed 
** to recursively displaying the reverse of a user-entered string, 
** recursively calculating the sum of N integers, and for recursively 
** calculating the triangular number for N.
*********************************************************************/
#ifndef MENU_HPP
#define MENU_HPP
#include "recursiveFunctions.hpp"

class Menu
{
private:
	recursiveFunctions functions;
public:
	Menu();
	void correctInput();
	void displayMenu();
};
#endif // !#MENU_HPP
#pragma once
