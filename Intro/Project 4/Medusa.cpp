/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the implementation code of the
** variables and functions needed for creating the Medusa creature
** and returning their attack points or defense points based on their
** dice specification. Medusa has a special ability called 'Glare'
** that kills her opponent, and causes Medusa to win.
*********************************************************************/
#include "Medusa.hpp"
#include <memory>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
/*********************************************************************
** Description: This is the default constructor which initializes the
** name, armor, and strength of the creature.
*********************************************************************/
Medusa::Medusa(string name) : Creature(3, 8, name)
{
	cout << "Medusa is ready to fight!" << endl;
}
/*********************************************************************
** Description: This is a function that simulates the rolling of two
** 6 sided die and then returns the sum of both rolls to represent the
** damage inflicted to their opponent. If Medusa rolls a 12, then the
** target has looked into her eyes and is turned to stone. Medusa wins
** in most cases with *Glare, except the Vampire's Charm ability trumps
** Medusa's ability, and also Harry Potter as he can come back to life. 
*********************************************************************/
int Medusa::getAttack()
{
	int roll = (rand() % 6 + 1) + (rand() % 6 + 1);
	if (roll == 12)
	{
		Glare();
		return 21;
	}
	else
	{
		return roll;
	}
}
/*********************************************************************
** Description: This is a function that notifies the user that Medusa's
** ability has been activated.
*********************************************************************/
void Medusa::Glare()
{
	cout << "Medusa uses Glare!" << endl;
}
/*********************************************************************
** Description: This is a function that simulates the rolling of one
** 6 sided die and then returns the sum of the defense points rolled.
*********************************************************************/
int Medusa::getDefense()
{
	return rand() % 6 + 1;
}