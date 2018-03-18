/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This file contains the implentation code of the
** variables and functions needed for creating a new University object
**, setting and returning the name of the University, and printing
** information about each building and person of the University.
*********************************************************************/
#include "University.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::setw;
/*********************************************************************
** Description: This is the default constructor which receives a name
** to instantiate the University object.
*********************************************************************/
University::University()
{
	setName("");
}
/*********************************************************************
** Description: This is the overloaded constructor which receives a name
** to instantiate the University object.
*********************************************************************/
University::University(const string& name)
{
	setName(name);
}
/*********************************************************************
** Description: This is a function that receives a string name to set the
** name of the newly created object.
*********************************************************************/
void University::setName(const string& name)
{
	this->name = name;
}
/*********************************************************************
** Description: This is a function that returns the name of the object
** that called this function.
*********************************************************************/
string University::getName() const
{
	return name;
}
/*********************************************************************
** Description: This is a function that prints out all the attributes
** of every building stored in the program.
*********************************************************************/
void University::print_Building_Info(const string name, const double sqft, const string address)
{
	cout << setw(25) << name << setw(6) << sqft << " sqft" << setw(45) << address << endl;
}
/*********************************************************************
** Description: This is a function that prints out all the attributes
** of every student or instructor stored in the program.
*********************************************************************/
void University::print_People_Info(const string name, const int age, const double gpa_or_rating, const int hours)
{
	cout << setw(25) << name << setw(5) << age << setw(8) << gpa_or_rating << setw(8) << hours << endl;
}
