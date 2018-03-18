/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the class specifications of the
** variables and functions needed for creating a new Barbarian creature
** and returning their attack points or defense points based on their
** dice specification.
*********************************************************************/
#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP
#include "Creature.hpp"
class Barbarian : public Creature
{
private:
public:
	Barbarian();
	virtual int getAttack();
	virtual int getDefense();
};
#endif // !BARBARIAN_HPP
