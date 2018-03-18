/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the class specifications of the
** variables and functions needed for creating a the Blue Men creatures
** and returning their attack points or defense points based on their
** dice specification.
*********************************************************************/
#include "BlueMen.hpp"
#include <memory>
#include <iostream>
#include <cstdlib>
using std::string;
using std::cout;
using std::endl;
/*********************************************************************
** Description: This is the default constructor which initializes the
** name, armor, and strength of the creature.
*********************************************************************/
BlueMen::BlueMen(string name) : Creature(3, 12, name)
{
	cout << "The Blue Men are ready to fight!" << endl;
}
/*********************************************************************
** Description: This is a function that simulates the rolling of two
** 10 sided die and then returns the sum of both rolls to represent the
** damage inflicted to their opponent.
*********************************************************************/
int BlueMen::getAttack()
{
	return (rand() % 10 + 1) + (rand() % 10 + 1);
}
/*********************************************************************
** Description: This is a function that simulates the rolling of three 
** 6 sided die to return defense points to the creature. However, everytime
** the Blue Men 4 strength, they lose 1 die that they can roll with
** to receive their defense points.
*********************************************************************/
int BlueMen::getDefense()
{
	if (strength <= 4)
	{
		cout << "The Blue Men are using 1d6 for defense now!" << endl;
		return (rand() % 6 + 1);
	}
	else if (strength <= 8)
	{
		cout << "The Blue Men are using 2d6 for defense now!" << endl;
		return (rand() % 6 + 1) + (rand() % 6 + 1);
	}
	else
	{
		return (rand() % 6 + 1) + (rand() % 6 + 1) + (rand() % 6 + 1);
	}
}
