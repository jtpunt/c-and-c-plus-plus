/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the implentation code of the
** variables and functions needed for creating a new Barbarian creature
** and returning their attack points or defense points based on their
** dice specification.
*********************************************************************/
#include "Barbarian.hpp"
#include <iostream>
#include <cstdlib>
using std::string;
using std::cout;
using std::endl;
/*********************************************************************
** Description: This is the default constructor which initializes the
** name, armor, and strength of the creature.
*********************************************************************/
Barbarian::Barbarian(string name) : Creature(0, 12, name)
{
	cout << "The Barbarian is ready to fight!" << endl;
}
/*********************************************************************
** Description: This is a function that simulates the rolling of two
** 6 sided die and then returns the sum of both rolls to represent the
** damage inflicted to their opponent.
*********************************************************************/
int Barbarian::getAttack()
{
	return (rand() % 6 + 1) + (rand() % 6 + 1);
}
/*********************************************************************
** Description: This is a function that simulates the rolling of two
** 6 sided die and then returns the sum of the defense points rolled.
*********************************************************************/
int Barbarian::getDefense()
{
	return (rand() % 6 + 1) + (rand() % 6 + 1);
}
