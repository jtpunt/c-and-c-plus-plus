/*********************************************************************
** Author: Jonathan Perry
** Date: 3/15/2017
** Description: This file contains the implementation code of
** the variables and functions needed for storing customer data such
** as their name, account ID number, whether or not they're a
** premium member of the store, and what products they currently have
** in their cart for making a purchase.
*********************************************************************/
#include "Customer.hpp"
using namespace std;
/*********************************************************************
** Description: This is a constructor of the Customer class which
** receives 3 variables with which to initialize the Customer's name, 
** account ID, and premium member status.
*********************************************************************/
Customer::Customer(string n, string a, bool pm)
{
	name = n;
	accountID = a;
	premiumMember = pm;
}
string Customer::getAccountID()
{
	return accountID;
}
/*********************************************************************
** Description: This is a member function which returns a vector of
** product ID(s) in the customer's cart.
*********************************************************************/
vector<string> Customer::getCart()
{
	return cart;
}
/*********************************************************************
** Description: This is a member function which adds the product ID 
** code to the customer's cart.
*********************************************************************/
void Customer::addProductToCart(string productToCart)
{
	cart.push_back(productToCart);
}
/*********************************************************************
** Description: This is a member function which returns whether the 
** customer is a premium member.
*********************************************************************/
bool Customer::isPremiumMember()
{
	if (premiumMember)
		return true;
	else
		return false;
}
/*********************************************************************
** Description: This is a member function which removes all products 
** from the customer's cart.
*********************************************************************/
void Customer::emptyCart()
{
	cart.clear();
}