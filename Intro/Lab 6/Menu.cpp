/*********************************************************************
** Author: Jonathan Perry
** Date: 5/07/2017
** Description: This file contains the implementation code of the
** variables and functions needed for displaying options to the user for
** adding/deleting nodes to the head of list, adding/deleting nodes at
** the tail of the list, displaying the contents of the list, and displaying
** the contents of the list in reverse order.
*********************************************************************/
#include "Menu.hpp"
#include <memory>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;                                                                        
/*********************************************************************
** Description: This is the default constructor which creates instantiates
** 1 student, 1 instructor, and 2 buildings und
*********************************************************************/
Menu::Menu()
{
	displayMenu();
	cout << "Welcome to my linked list!" << endl;
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
	cout << "\n___________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Add a new node to the head:			                |" << endl;
	cout << "|2. Add a new node to the tail:                            |" << endl;
	cout << "|3. Delete from head:                                      |" << endl;
	cout << "|4. Delete from tail:                                      |" << endl;
	cout << "|5. Traverse the list reversely:                           |" << endl;
	cout << "|6. Exit:                                                  |" << endl;
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
		list.addHead(userInput);
		list.displayList();
		displayMenu();
		break;
	case 2:
		cout << "Please enter a positive integer: ";
		cin >> userInput;
		while (!cin)
		{
			correctInput();
			cin >> userInput;
		}
		list.addTail(userInput);
		list.displayList();
		displayMenu();
		break;
	case 3:
		list.removeHead();	
		list.displayList();
		displayMenu();
		break;
	case 4:
		list.removeTail();
		list.displayList();
		displayMenu();
		break;
	case 5:
		list.reverseList();
		displayMenu();
		break;
	case 6:
		exit(0);
		break;
	default:
		correctInput();
		cout << "Invalid input entered, please try again: " << endl;
		displayMenu();
		break;
	}
}
int main()
{
	Menu menu;
	return 0;
}

