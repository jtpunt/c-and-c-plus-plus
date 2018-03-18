/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This file contains the implentation code of the
** variables and functions needed for creating a new People object
**, setting and returning the name of the person, and setting and returning
** the age of the person.
*********************************************************************/
#include "People.hpp"
using std::string;
/*********************************************************************
** Description: This is the default constructor which receives the name
** of the person and their age to instantiate the People object.
*********************************************************************/
People::People(const string &name, int age) : University(name)
{
	this->age = age;
}
/*********************************************************************
** Description: This is a function that receives an integer (age) to
** set the age of the person.
*********************************************************************/
void People::setAge(int age)
{
	this->age = age;
}
/*********************************************************************
** Description: This is a function that returns the age of the person.
*********************************************************************/
int People::getAge()
{
	return age;
}