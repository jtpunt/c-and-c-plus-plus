/*********************************************************************
** Author: Jonathan Perry
** Date: 5/1/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for storing, deleting, and displaying 
** grocery list item's.
*********************************************************************/
#ifndef LIST_HPP
#define LIST_HPP
#include "Item.hpp"
class List
{
private:
	// Dynamic array used to allocate space for each new item
	Item **item;
	int i = 0; // Stores the current size of the array
public:
	List(); // Initializes the array to hold 4 items
	~List(); // Dynamically deallocates space used for the array
	void clearInput();
	// Compares names of two Item objects to see if they're the same
	friend bool operator==(const Item &, const Item &);
	// Receives the name, unit, price, and quantity to buy to create another item
	void addItem(std::string, std::string, double, int);
	// Prompts the user to change item information after adding a duplicate item to the list
	void updateList(Item &);
	// Receives the name of an item to remove from the list
	void removeItem(std::string);
	// Pushes the item to be removed to the back of the list before removal
	void listSwap(Item&, Item&);
	// Displays the current items on the grocery list
	void displayItems();
};
#endif // !LIST_HPP
