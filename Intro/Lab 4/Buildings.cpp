/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This file contains the implentation code of the
** variables and functions needed for creating a new Building object
**, setting and returning the size of the Building, and setting and returning
** the address of the building.
*********************************************************************/
#include "Buildings.hpp"
using std::string;
/*********************************************************************
** Description: This is the default constructor which receives the name
** of the building, its size, and address to instantiate the Building
** object.
*********************************************************************/
Buildings::Buildings(const string& name, int size, const string& address) : University(name)
{
	setSize(size);
	setAddress(address);
}
/*********************************************************************
** Description: This is a function that receives an integer (size) to
** set the size of the building.
*********************************************************************/
void Buildings::setSize(const int size)
{
	this->size = size;
}
/*********************************************************************
** Description: This is a function that returns the size of the building
** in sqft.
*********************************************************************/
int Buildings::getSize() const
{
	return size;
}
/*********************************************************************
** Description: This is a function that receives an address string
** to set the address of the building.
*********************************************************************/
void Buildings::setAddress(const string & address)
{
	this->address = address;
}
/*********************************************************************
** Description: This is a function that returns the address string
** of the building.
*********************************************************************/
string Buildings::getAddress() const
{
	return address;
}