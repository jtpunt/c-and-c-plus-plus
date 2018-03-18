/*********************************************************************
** Author: Jonathan Perry
** Date: 5/28/2017
** Description: This file contains the implementation code of the
** variables and functions needed for displaying options to the user
** so that they may search for values within a text file, and sort
** those values using a bubble sort algorithm, and then finally search
** through the original file's values and the sorted values using a
** binary search algorithm.
*********************************************************************/
#include "Menu.hpp"
#include <memory>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;                                                                        
/*********************************************************************
** Description: This is the default constructor displays the main menu
** to the user.
*********************************************************************/
Menu::Menu()
{
	displayMenu();
}
/*********************************************************************
** Description: This is a function resets any error flags for cin
** and discards up to 1,000 characters from the input buffer.
*********************************************************************/
void Menu::correctInput()
{
	cout << "Please enter a positive integer.";
	// resets any error flags for cin if anything but integers are entered
	cin.clear();
	// Discards up to 1,000 characters from the input buffer or until a newline is read
	cin.ignore(1000, '\n');
}
/*********************************************************************
** Description: This is a function that prints out the menu to the current
** users to give them options on navigating through the program.
*********************************************************************/
void Menu::displayMenu()
{
	int menuChoice = 0, userInput = 0;
	cout << endl;
	cout << "____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Search for the target value (i.e. 0)                   |" << endl;
	cout << "|2. Sort a set of values and then output it:               |" << endl;
	cout << "|3. Search for the target value (binary search algorithm): |" << endl;
	cout << "|4. Exit:                                                  |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		cout << "Please enter a positive integer: ";
		cin >> userInput;
		while (!cin)
		{
			correctInput();
			cin >> userInput;
		}
		search.searchValue(userInput);
		displayMenu();
		break;
	case 2:
		search.startSort();
		displayMenu();
		break;
	case 3:
		cout << "Please enter a positive integer: ";
		cin >> userInput;
		while (!cin)
		{
			correctInput();
			cin >> userInput;
		}
		search.searchValue(userInput);
		search.startBinarySearch(userInput);
		displayMenu();
		break;
	case 4:
		exit(0);
		break;
	default:
		correctInput();
		cout << "Invalid input entered, please try again: " << endl;
		displayMenu();
		break;
	}
}

