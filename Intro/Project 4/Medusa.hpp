/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the class specifications of the
** variables and functions needed for creating the Medusa creature
** and returning their attack points or defense points based on their
** dice specification. Medusa has a special ability called 'Glare'
** that kills her opponent, and causes Medusa to win.
*********************************************************************/
#ifndef MEDUSA_HPP
#define MEDUSA_HPP
#include "Creature.hpp"
class Medusa : public Creature
{
private:
public:
	Medusa(std::string);
	void Glare();
	virtual int getAttack();
	virtual int getDefense();
};
#endif // !MEDUSA_HPP
