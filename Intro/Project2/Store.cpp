/*********************************************************************
** Author: Jonathan Perry
** Date: 3/15/2017
** Description: This file defines the implementation code of the 
** variables and functions needed for storing and retreiving pointers
** to each individual customer and product, searching for a product,
** adding a product to a customer's cart, and checking out.
*********************************************************************/
#include "Store.hpp"
#include <iostream>
#include <iomanip>
using namespace std;
/*********************************************************************
** Description: This is a non-member function which receives
** returns a string in all lowercase characters.
*********************************************************************/
string toLowercase(string str)
{
	for (int i = 0; str[i]; i++)
	{
		// converts search word to lowercase
		str[i] = tolower(str[i]);
	}
	return str;
}
/*********************************************************************
** Description: This is a member function which adds a pointer to a 
** Product to the vector 'inventory'.
*********************************************************************/
void Store::addProduct(Product* p)
{
	inventory.push_back(p);
}
/*********************************************************************
** Description: This is a member function which adds a pointer to a
** Customer to the vector 'members'.
*********************************************************************/
void Store::addMember(Customer* c)
{
	members.push_back(c);
}
/*********************************************************************
** Description: This is a member function which returns a pointer to 
** Product with a matching ID and returns NULL if no matching ID is found.
*********************************************************************/
Product* Store::getProductFromID(string prodID)
{
	// Receives a Product each iteration through the vector inventory
	for (Product* i : inventory)
	{
		if (i->getIdCode() == prodID)
		{
			return i;
		}
	}
	return NULL;
}
/*********************************************************************
** Description: This is a member function which returns a pointer to
** Customer with matching ID and returns NULL if no matching ID is found.
*********************************************************************/
Customer* Store::getMemberFromID(string memID)
{
	// Receives a Customer each iteration through the vector members
	for (Customer* i : members)
	{
		if (i->getAccountID() == memID)
		{
			return i;
		}
	}
	return NULL;
}
/*********************************************************************
** Description: This is a member function which receives a string to
** search for a Product with a matching title or description and then 
** prints out that product's title, ID, price, and description when a
** match is found. The search word, title, and description are all 
** converted to lowercase before being compared to for a match.
*********************************************************************/
void Store::productSearch(string str)
{
	// Converts search word to lowercase
	str = toLowercase(str);
	// Receives a Product each iteration through the vector inventory
	for(Product* i : inventory)
	{
		// Converts title and description to lowercase
		string title = toLowercase(i->getTitle());
		string description = toLowercase(i->getDescription());
		// Compares the search string to a title and description to find a match
		if (title.find(str) != string::npos || description.find(str) != string::npos)
		{
			cout << setprecision(2) << showpoint << fixed;
			cout << i->getTitle() << "\nID Code: " << i->getIdCode() << endl;
			cout << "price: " << i->getPrice() << "\n" << i->getDescription() << "\n" << endl;
		}
	}
}
/*********************************************************************
** Description: Receives a product ID and member ID and after validating
** both, adds the product to the customer's cart if the the quantity 
** available of that product is greater than zero.
*********************************************************************/
void Store::addProductToMemberCart(string pID, string mID)
{
	// Returns and stores a pointer to a Product with matching ID
	Product* productID = getProductFromID(pID);
	// Returns and stores a pointer to a Customer with matching ID
	Customer* memberID = getMemberFromID(mID);
	if (productID == NULL)
	{
		cout << "Product #" << pID << " not found." << endl;
	}
	if (memberID == NULL)
	{
		cout << "Member #" << mID << " not found." << endl;
	}
	if (!(productID == NULL || memberID == NULL))
	{
		// Check that the product isn't out of stock
		if (productID->getQuantityAvailable() > 0)
		{
			memberID->addProductToCart(pID);
		}
		else
			cout << "Sorry, product #" << pID << " is currently out of stock." << endl;
	}
}
/*********************************************************************
** Description: Receives and validates a member ID and if it's valid,
** prints out each currently in stock title and price of the product(s)
** retrieved from the customer's cart and then prints out the
** subtotal, shipping cost, and total cost before emptying their cart.
*********************************************************************/
void Store::checkOutMember(string mID)
{
	// Returns and stores a pointer to a Customer with matching ID
	Customer* memID = getMemberFromID(mID);
	// Returns and stores the customer's cart of products
	vector <string> cart = memID->getCart();
	double subtotal = 0.0, shippingCost = 0.0;

	if (memID == NULL)
	{
		cout << "Member #" << mID << " not found." << endl;
	}
	else if(cart.empty())
	{
		cout << "There are no items in the cart." << endl;
	}
	else
	{
		// Receives a product ID each iteration through the cart
		for(const string product_ID: cart)
		{
			// Returns and stores a pointer to a Product with matching ID
			Product* productID = getProductFromID(product_ID);
			// Check that the product isn't out of stock
			if (productID->getQuantityAvailable() > 0)
			{
				cout << setprecision(2) << showpoint << fixed;
				cout << productID->getTitle() << " - $" << productID->getPrice() << endl;
				subtotal += productID->getPrice();
				productID->decreaseQuantity();
			}
			else // Product is not in stock
			{
				cout << "Sorry, product #" << productID->getIdCode();
				cout << ", \"" << productID->getTitle() << "\", is no longer available." << endl;
			}
		}
		// Check customer for premium member status
		if (!(memID->isPremiumMember()))
		{
			// Charge non-premium members for shipping
			shippingCost = subtotal * .07;
			// Charge premium members nothing for shipping
		}
		cout << setprecision(2) << showpoint << fixed;
		cout << "Subtotal: $" << subtotal << "\nShipping Cost: $";
		cout << shippingCost << "\nTotal: $" << subtotal + shippingCost << endl;
		// Empty the customer's cart
		memID->emptyCart();
	}
}