/*********************************************************************
** Author: Jonathan Perry
** Date: 6/03/2017
** Description: This file contains the implementation code of the
** variables and functions needed for displaying options to the user
** so that they may create a palindrome and to add or remove numbers 
** from a queue based on a percent chance, which is set by the user
** in this menu.
*********************************************************************/
#include "Menu.hpp"
#include <string>
#include <memory>
#include <iostream>
using std::string;
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
	int menuChoice = 0;
	cout << "\n____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Add or remove a number from the queue:                 |" << endl;
	cout << "|2. Create a palindrome:                                   |" << endl;
	cout << "|3. Exit:                                                  |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		cout << "How many rounds do you want to play? MAX 20: ";
		cin >> roundNumbers;
		while (!cin || roundNumbers <= 0 || roundNumbers > 20)
		{
			correctInput();
			cout << "How many rounds do you want to play? MAX 20: ";
			cin >> roundNumbers;
		}
		queueMenu();
		break;
	case 2:
		stackMenu();
		break;
	case 3:
		exit(0);
		break;
	default:
		correctInput();
		cout << "Invalid input entered, please try again: " << endl;
		displayMenu();
		break;
	}
}
/*********************************************************************
** Description: This is a function that prints out the secondary menu 
** to the current users to give them options on adding a random number 
** between 1 and 1000 into the back of the queue and removing the number 
** at the front of the queue. However, these operations are only done 
** when a random number between 1 and 100 is less than a user-entered
** number that is also restricted to 1 and 100.
*********************************************************************/
void Menu::queueMenu()
{
	int menuChoice = 0;
	bool option1 = false;
	bool option2 = false;
	cout << "\n____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Add the number into the back of the queue and          |" << endl;
	cout << "|   then remove the front number from the queue:           |" << endl;
	cout << "|2. Go back to the main menu:                              |" << endl;
	cout << "|3. Exit:                                                  |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		if (roundNumbers > 0)
		{
			for (int i = 0; i < roundNumbers; i++)
			{
				bool result = false;
				bool result1 = false;

				cout << "\nRound number: " << i + 1 << endl;

				do
				{
					result = addToBuffer();
				} while (!result); // keep looping until valid input is entered
				do
				{
					result1 = removeFromBuffer();
				} while (!result1);// keep looping until valid input is entered
			}
			myQueue.resetQueue(); // clear the queue of all data
			roundNumbers = 0;
		}
		else
		{
			cout << "Please go back and re-enter the number of rounds to play." << endl;
		}
		queueMenu();
	case 2:
		myQueue.resetQueue(); // clear the queue of all data
		roundNumbers = 0; // reset to 0 in case the function is called again
		displayMenu();
		break;
	case 3:
		exit(0);
		break;
	default:
		correctInput();
		cout << "Invalid input entered, please try again: " << endl;
		queueMenu();
		break;
	}
}
/*********************************************************************
** Description: This is a function that displays user menu options to 
** the user for entering in any word to create the palindrome, options 
** for going back to the main menu, and options for exiting the program.
*********************************************************************/
void Menu::stackMenu()
{
	int menuChoice = 0;
	string stringInput;
	cout << endl;
	cout << "____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Enter in any word to create the palindrome:            |" << endl;
	cout << "|2. Go back to the main menu:                              |" << endl;
	cout << "|3. Exit:                                                  |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		cout << "Enter in any word of your choice: ";
		cin >> stringInput;
		// Pushes each individual character onto the stack
		for (int i = 0; i < stringInput.length(); i++)
		{
			myStack.pushValue(stringInput.at(i));
		}
		// Displays the reverse of the string the user entered, creating the palindrome
		myStack.displayPalindrome(stringInput.length() - 1);
		stackMenu();
		break;
	case 2:
		displayMenu();
		break;
	case 3:
		exit(0);
		break;
	default:
		correctInput();
		cout << "Invalid input entered, please try again: " << endl;
		stackMenu();
		break;
	}
}
/*********************************************************************
** Description: This is a function that gets the user-input on the 
** percent chance they want to set for adding or removing values from the
** buffer. If the user enteres a number greater than 100 or less than 1,
** an outOfRange exception is thrown which causes this function to be 
** called again in an loop that can only break by entering in a valid 
** number.
*********************************************************************/
int Menu::getInput()
{
	int userInput;
	cout << "\nEnter in a number between 1 and 100: ";
	cin >> userInput;
	if (userInput < 1 || userInput > 100)
	{
		throw outOfRange();
	}
	return userInput;
}
/*********************************************************************
** Description: This is a function that tries to get valid input gathered
** from calling getInput(). However, if an exception is thrown by getInput(),
** this exception is caught and this function then returns false, after
** notifying the user to enter in valid input. The false return value 
** causes this function to be called again in an loop until a valid 
** number is entered. If no exceptions are thrown, the user-specified 
** percentage to sent to the pushToBuffer function to possibly push
** push a random number between 1 and 1000 into the buffer.
*********************************************************************/
bool Menu::addToBuffer()
{
	try
	{
		int number = getInput();
		myQueue.pushToBuffer(number);
		myQueue.displayBuffer();
		return true;
	}
	catch (Menu::outOfRange)
	{
		cout << "Please enter a number between 1 and 100";
		return false;
	}
}
/*********************************************************************
** Description: This is a function that tries to get valid input gathered
** from calling getInput(). However, if an exception is thrown by getInput(),
** this exception is caught and this function then returns false, after
** notifying the user to enter in valid input. The false return value
** causes this function to be called again in an loop until a valid
** number is entered. If no exceptions are thrown, the user-specified
** percentage to sent to the removeFromBuffer function to possibly pop
** the number off of the front of the queue.
*********************************************************************/
bool Menu::removeFromBuffer()
{
	try
	{
		int number = getInput();
		myQueue.removeFromBuffer(number);
		myQueue.displayBuffer();
		return true;
	}
	catch (Menu::outOfRange)
	{
		cout << "Please enter a number between 1 and 100";
		return false;
	}
}


