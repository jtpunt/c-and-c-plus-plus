/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the class specifications of the
** variables and functions needed for creating a the Blue Men creatures
** and returning their attack points or defense points based on their
** dice specification.
*********************************************************************/
#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP
#include "Creature.hpp"
class BlueMen : public Creature
{
private:
public:
	BlueMen(std::string);
	virtual int getAttack();
	virtual int getDefense();
};
#endif // !#BLUEMEN_HPP
