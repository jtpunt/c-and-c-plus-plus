/*********************************************************************
** Author: Jonathan Perry
** Date: 5/1/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for creating grocery
** list item's such as the item's name, unit type, unit price, and the
** specified quantity to buy.
*********************************************************************/
#include "Item.hpp"
using std::string;
/*********************************************************************
** Description: This is a constructor of the Item class which receieves
** 4 variables to initialize the item's name, unit type, price, and the 
** quantity to buy.
*********************************************************************/
Item::Item(string name, string unit, double unitPrice, int quantityToBuy)
{
	setName(name);
	setUnit(unit);
	setUnitPrice(unitPrice);
	setQuantityToBuy(quantityToBuy);
}
/*********************************************************************
** Description: This is a function that sets the name of the item.
*********************************************************************/
void Item::setName(const string name)
{
	this->name = name;
}
/*********************************************************************
** Description: This is a function that returns the name of the item.
*********************************************************************/
string Item::getName() const
{
	return name;
}
/*********************************************************************
** Description: This is a function that sets the unit type of the item.
*********************************************************************/
void Item::setUnit(const string unit)
{
	this->unit = unit;
}
/*********************************************************************
** Description: This is a function that returns the unit type of the item.
*********************************************************************/
string Item::getUnit() const
{
	return unit;
}
/*********************************************************************
** Description: This is a function that sets the price of the item.
*********************************************************************/
void Item::setUnitPrice(const double unitPrice)
{
	this->unitPrice = unitPrice;
}
/*********************************************************************
** Description: This is a function that returns the price of the item.
*********************************************************************/
double Item::getUnitPrice() const
{
	return unitPrice;
}
/*********************************************************************
** Description: This is a function that sets the quantity amount to 
** buy.
*********************************************************************/
void Item::setQuantityToBuy(const int quantityToBuy)
{
	this->quantityToBuy = quantityToBuy;
}
/*********************************************************************
** Description: This is a function that return the quantity amount to
** buy.
*********************************************************************/
int Item::getQuantityToBuy() const
{
	return quantityToBuy;
}
/*********************************************************************
** Description: This is a function returns the extended price of the item.
*********************************************************************/
double Item::getExtendedPrice() const
{
	return this->getQuantityToBuy() * this->getUnitPrice();
}
