/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the class specifications of the
** variables and functions needed for creating and managing creatures
** by setting  and retrieving the creatures' name, strength, and armor.
** This file also include an overloaded operator that simulates each 
** attack from creature to creature.
*********************************************************************/
#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <string>
class Creature
{
protected:
	int attack, defense, armor, strength;
	std::string  creatureName; 
public:
	Creature();
	Creature(const int, const int, std::string);
	friend int operator-(Creature &, Creature &); // For calculating amount of strength left after attack
	int restoreHealth();
	void setArmor(const int);
	void setStrength(const int);
	void setName(const std::string);
	int getArmor();
	virtual int getStrength();
	std::string getName();
	virtual int getAttack() = 0; // Virtual functions to call specific function from derived classes
	virtual int getDefense() = 0;
};
#endif // !CREATURE_HPP
  