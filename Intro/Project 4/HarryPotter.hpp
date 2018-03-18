/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the class specifications of the
** variables and functions needed for creating the Harry Potter creature
** and returning their attack points or defense points based on their
** dice specification. Harry has a special ability called 'Hogwarts'
** where Harry resurrects after dying.
*********************************************************************/
#ifndef HARRYPOTTER_HPP
#define HARRYPOTTER_HPP
#include "Creature.hpp"
class HarryPotter : public Creature
{
private:
	bool revives = false; // Is turned to true after the first revive
public:
	HarryPotter(std::string);
	virtual int getStrength() override;
	virtual int getAttack();
	virtual int getDefense();
	void Hogwarts();
};
#endif // !HARRYPOTTER_HPP