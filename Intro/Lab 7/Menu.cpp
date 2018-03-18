/*********************************************************************
** Author: Jonathan Perry
** Date: 5/22/2017
** Description: This file contains the implementation code of the
** variables and functions needed for displaying options to the user
** so that they may add nodes to the back of the queue, display the
** value stored in the node at the front of the queue, remove the
** node at the front of the queue, and display every value from the
** front node to the rear node, and exit.
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
	cout << "|1. Enter a value to be added to the queue:                |" << endl;
	cout << "|2. Display first node (front) value:                      |" << endl;
	cout << "|3. Remove first node (front) value:                       |" << endl;
	cout << "|4. Display the queue contents:                            |" << endl;
	cout << "|5. Exit:                                                  |" << endl;
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
		myQueue.addBack(userInput);
		displayMenu();
		break;
	case 2:
		if (myQueue.getFront() != NULL)
		{
			cout << myQueue.getFront() << endl;
		}
		displayMenu();
		break;
	case 3:
		myQueue.removeFront();
		displayMenu();
		break;
	case 4:
		myQueue.displayQueue();
		displayMenu();
		break;
	case 5:
		exit(0);
		break;
	default:
		correctInput();
		cout << "Invalid input entered, please try again: " << endl;
		displayMenu();
		break;
	}
}

