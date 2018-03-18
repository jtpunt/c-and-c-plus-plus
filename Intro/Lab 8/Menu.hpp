/*********************************************************************
** Author: Jonathan Perry
** Date: 5/28/2017
** Description: This file contains the class specification of the
** variables and functions needed for displaying options to the user
** so that they may search for values within a text file, and sort
** those values using a bubble sort algorithm, and then finally search
** through the original file's values and the sorted values using a
** binary search algorithm.
*********************************************************************/
#ifndef MENU_HPP
#define MENU_HPP
#include "searchAlgorithm.hpp"
class Menu
{
private:
	searchAlgorithm search;
public:
	Menu();
	void correctInput();
	void displayMenu();
};
#endif // !#MENU_HPP

