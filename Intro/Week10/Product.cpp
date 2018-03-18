/*********************************************************************
** Author: Jonathan Perry
** Date: 3/15/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for storing and retrieving product
** data such as the product's ID, title, description, price, and the
** current quantity that's available.
*********************************************************************/
#include "Product.hpp"
using namespace std;
/*********************************************************************
** Description: This is a constructor of the Product class which receieves
** 5 variables with which to initialize the product's idCode, title, 
** description, price, and quantity available.
*********************************************************************/
Product::Product(string id, string t, string d, double p, int qa)
{
	idCode = id;
	title = t;
	description = d;
	price = p;
	quantityAvailable = qa;
}
string Product::getIdCode()
{
	return idCode;
}
string Product::getTitle()
{
	return title;
}
string Product::getDescription()
{
	return description;
}
double Product::getPrice()
{
	return price;
}
int Product::getQuantityAvailable()
{
	return quantityAvailable;
}
/*********************************************************************
** Description: This is a member function which decrements the quantity
** available by 1 of the product in question.
*********************************************************************/
void Product::decreaseQuantity()
{
	quantityAvailable--;
}