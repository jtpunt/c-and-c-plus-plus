/*********************************************************************
** Author: Jonathan Perry
** Date: 5/1/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for storing, deleting, and displaying 
** grocery list item's.
*********************************************************************/
#include "List.hpp"
#include <iostream>
#include <iomanip>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::getline;
/*********************************************************************
** Description: This is a constructor of the List class which 
** initializes the array to hold 4 items.
*********************************************************************/
List::List()
{
	item = new Item*[4];
}
/*********************************************************************
** Description: This is a destructor of the List class which deallocates
** memory used with the array.
*********************************************************************/
List::~List()
{
	for (int k = 0; k < i; k++)
	{
		delete item[k];
	}
	delete[] item;
}
/*********************************************************************
** Description: This is a function that resets any error flags for cin
** and discards up to 1,000 characters from the input buffer.
*********************************************************************/
void List::clearInput()
{
	cout << "Please enter a positive integer: ";
	cin.clear();
	// Discards up to 1,000 characters from the input buffer or until a newline is read
	cin.ignore(1000, '\n');
}
/*********************************************************************
** Description: This is an operator which compares the names of two 
** item objects to see if they're the same.
*********************************************************************/
bool operator==(const Item &item1, const Item &item2)
{
	return item1.getName() == item2.getName();
}
/*********************************************************************
** Description: This is a function that receives the item's name, unit,
** price, and quantity to buy to create a new non-duplicate item and 
** add it onto the grocery list. If the user tries to add a duplicate item,
** then the user is asked if they want to update the information on the
** item that's already on the grocery list.
*********************************************************************/
void List::addItem(string name, string unit, double unitPrice, int quantityToBuy)
{
	// Creates a pointer to the Item object to check if it already exists
	Item* newItem = new Item(name, unit, unitPrice, quantityToBuy);
	// Overloading the == operator to see if the item is already in the list
	for(int k = 0; k < i; k++)
	{
		// Creates a pointer to each Item object on the grocery list
		Item* checkItem = item[k];
		// True - the objects are the same
		if (*newItem == *checkItem)
		{
			// Ask the user to update the item
			updateList(*checkItem);
			// Delete the duplicate item
			delete newItem;
			newItem = nullptr;
		}
	}
	// Add the non-duplicate item onto the grocery list
	if (newItem != NULL)
	{
		cout << "Item Name: " << newItem->getName() << " successfully added!" << endl;
		item[i++] = newItem;
	}
}
/*********************************************************************
** Description: This is a function that prompts the user to update item
** information on an item already on the list after the user tries to 
** add a duplicate item.
*********************************************************************/
void List::updateList(Item & changeItem)
{
	int input, quantityToBuy;
	double unitPrice;
	string itemName, unit;
	cout << "That item is already on this list, do you wish to update it? " << endl;
	cout << "Enter 0 for no: " << endl;
	cout << "Enter 1 for yes: ";
	cin >> input;
	if (input == 1)
	{
		cout << "\nUnit(i.e. can, box, pound, or ounce): ";
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
		cout << "Quantity to Buy:";
		cin >> quantityToBuy;
		while (!cin || quantityToBuy < 0)
		{
			clearInput();
			cin >> quantityToBuy;
		}
		changeItem.setUnit(unit);
		changeItem.setUnitPrice(unitPrice);
		changeItem.setQuantityToBuy(quantityToBuy);
	}
}
/*********************************************************************
** Description: This is a function that receives the name of the item
** to be removed and then checks each item on the list for a matching
** item name. Once a match has been found, the item is swapped with 
** item below it on the list until it is at the end of the list and then
** finally it is removed.
*********************************************************************/
void List::removeItem(string name)
{
	for (int k = 0; k < i; k++)
	{
		// Search each name of the dynamic array for a matching name
		if (item[k]->getName() == name)
		{
			cout << "Item Name: " << item[k]->getName() << " found! Removing item:" << endl;
			// Moves the item to the end of the array
			while (k < i - 1)
			{
				listSwap(*item[k], *item[k + 1]);
				k++;
			}
			// deletes the item after it is placed at the end of the array
			delete item[k];
			// Adjusts i to the new size of the array
			i--;
		}
	}
	cout << "Item name: " << name << " not found! " << endl;
}
/*********************************************************************
** Description: This is a function that receives two item objects from
** the grocery list and swaps their positions so that object that needs
** to be deleted will end up at the bottom of the list and then can be 
** easily removed.
*********************************************************************/
void List::listSwap(Item& item1, Item& item2)
{
	Item temp = item2;
	item2 = item1;
	item1 = temp;
}
/*********************************************************************
** Description: This is a function that displays the item name, unit type,
** unit price, the quantity to buy, and the extended price of every item
** currently added to the grocery list before finally printing out the
** total price at the bottom.
*********************************************************************/
void List::displayItems()
{
	double totalPrice = 0;
	cout << setw(20) << "Item Name" << setw(11) << "Unit Type" << setw(12) << "Unit Price";
	cout << setw(17) << "Quantity to Buy" << setw(16) << "Extended Price" << endl;
	for (int k = 0; k < i; k++)
	{
		cout << setw(20) << item[k]->getName() << setw(11) << item[k]->getUnit();
		cout << setw(3) << "$" << setw(9) << item[k]->getUnitPrice() << setw(17) << item[k]->getQuantityToBuy();
		cout << setw(3) << "$" << setw(13) << item[k]->getExtendedPrice() << endl;
		totalPrice += item[k]->getExtendedPrice();
	}
	cout << setw(71) << "Total Price: $" << totalPrice << endl;
}