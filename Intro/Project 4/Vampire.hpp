/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the class specifications of the
** variables and functions needed for creating the Vampire creature
** and returning their attack points or defense points based on their
** dice specification. The Vampire creature has a special ability called
** 'Charm' that causes their opponent to not attack.
*********************************************************************/
#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP
#include "Creature.hpp"
class Vampire : public Creature
{
private:
public:
	Vampire(std::string);
	void charmOpponent();
	virtual int getAttack();
	virtual int getDefense();
};
#endif // !VAMPIRE_HPP
