/*********************************************************************
** Author: Jonathan Perry
** Date: 5/07/2017
** Description: This file contains the implentation code of the
** variables and functions needed for gathering all user-input needed 
** to recursively displaying the reverse of a user-entered string, 
** recursively calculating the sum of N integers, and for recursively 
** calculating the triangular number for N.
*********************************************************************/
#include "Menu.hpp"
#include <string>
#include <memory>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;                                                                        
using std::getline;
using std::string;
using std::unique_ptr;
/*********************************************************************
** Description: This is the default constructor which creates instantiates
** 1 student, 1 instructor, and 2 buildings und
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
	int menuChoice = 0, arraySize = 0, triangularNumber = 0;
	string inputString = "";
	cout << "\n____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. See the reverse of any word or sentence:               |" << endl;
	cout << "|2. See the sum of an array:                               |" << endl;
	cout << "|3. See the triangular number for N:                       |" << endl;
	cout << "|4. Exit                                                   |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		cout << "Enter a string and I'll show you the reverse of it: " << endl;
		getline(cin, inputString);
		functions.reverseString(inputString);
		displayMenu();
		break;
	case 2:
		cout << "How many numbers do you want in your array? ";
		cin >> arraySize;
		functions.createArray(arraySize);
		displayMenu();
		break;
	case 3:
		cout << "What is the triangular number you wish to calculate? ";
		cin >> triangularNumber;
		functions.triangularN(triangularNumber);
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
int main()
{
	Menu menu;
	return 0;
}

