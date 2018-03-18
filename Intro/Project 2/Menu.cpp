/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This file contains the implentation code of the
** variables and functions needed for creating and managing a list
** of grocery items.
*********************************************************************/
#include "Menu.hpp"
#include <string>
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::string;
/*********************************************************************
** Description: This is a constructor of the Menu class which creates
** the List object and then displays the main menu to the user.
*********************************************************************/
Menu::Menu()
{
	displayMenu();
}
/*********************************************************************
** Description: This is a function that resets any error flags for cin
** and discards up to 1,000 characters from the input buffer.
*********************************************************************/
void Menu::clearInput()
{
	cout << "Please enter a positive integer: ";
	cin.clear();
	// Discards up to 1,000 characters from the input buffer or until a newline is read
	cin.ignore(1000, '\n');
}
/*********************************************************************
** Description: This is a function that displays the menu to the user
** so that they may navigate through different features of the program.
*********************************************************************/
void Menu::displayMenu()
{
	int menuChoice = 0, menuChoice2 = 0, menuChoice3 = 0, menuChoice4 = 0, input = 0, quantityToBuy = 0;
	double unitPrice = 0.00;
	string itemName;
	string unit;
	string itemToRemove;
	cout << "____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Add Items                                              |" << endl;
	cout << "|2. Remove Items                                           |" << endl;
	cout << "|3. Display the shopping list                              |" << endl;
	cout << "|4. Exit                                                   |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		cout << "Please enter in item's name, unit type, the unit price, and the quantity you want to buy." << endl;
		cout << "\nItem Name: ";
		getline(cin, itemName);
		cout << "Unit(i.e. can, box, pound, or ounce): ";
		cin >> unit;
		while (unit != "can" && unit != "box" && unit != "pound" && unit != "ounce")
		{
			cout << "Please type in can, box, pound, or ounce: ";
			getline(cin, unit);
		}

		cout << "Unit Price: $";
		cin >> unitPrice;
		while (!cin || unitPrice < 0)
		{
			clearInput();
			cin >> unitPrice;
		}
		cout << "Quantity to Buy: ";
		cin >> quantityToBuy;
		while (!cin || quantityToBuy < 0)
		{
			clearInput();
			cin >> quantityToBuy;
		}
		list.addItem(itemName, unit, unitPrice, quantityToBuy);
		displayMenu();
		break;
	case 2:
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		list.displayItems();
		cout << "Please enter in the name of the item you want to remove: ";
		getline(cin, itemToRemove);
		list.removeItem(itemToRemove);
		displayMenu();
		break;
	case 3:
		list.displayItems();
		displayMenu();
		break;
	case 4:
		exit(0);
		displayMenu();
		break;
	default:
		cout << "Invalid input entered, please try again: " << endl;
		displayMenu();
		break;
	}
}
int main()
{
	Menu menu;
}