/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the implentation code of the
** variables and functions needed for creating a new Barbarian creature
** and returning their attack points or defense points based on their
** dice specification.
*********************************************************************/
#include "Vampire.hpp"
#include <memory>
#include <iostream>
using std::cout;
using std::endl;
/*********************************************************************
** Description: This is the default constructor which initializes the
** name, armor, and strength of the creature.
*********************************************************************/
Vampire::Vampire() : Creature(1, 18, "Vampire")
{
	cout << "The Vampire is ready to fight!" << endl;
}
/*********************************************************************
** Description: This is a function that notifies the user that the
** Vampire's special ability has been activated.
*********************************************************************/
void Vampire::charmOpponent()
{
	cout << "The Vampire's charm ability has been activated!" << endl;
}
/*********************************************************************
** Description: This is a function that simulates the rolling of one
** 12 sided die and then returns the sum of both rolls to represent the
** damage inflicted to their opponent.
*********************************************************************/
int Vampire::getAttack()
{
	return rand() % 12 + 1;
}
/*********************************************************************
** Description: This is a function that simulates the rolling of one
** 6 sided die and then returns the sum of the defense points rolled.
*********************************************************************/
int Vampire::getDefense()
{
	/* The vampire has a 50% of activating their charm ability
	   If the random number generator returns a number greater
	   than 50, the charm ability is activated */
	if (rand() % 100 + 1 > 50)
	{
		charmOpponent();
		return 22;
	}
	return rand() % 6 + 1;
}