/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the implementation code of the
** variables and functions needed for creating and managing creatures
** by setting  and retrieving the creatures' name, strength, and armor.
** This file also include an overloaded operator that simulates each
** attack from creature to creature.
*********************************************************************/
#include "Creature.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
/*********************************************************************
** Description: This is the default constructor which initializes the
** name, armor, and strength of the creature to zero.
*********************************************************************/
Creature::Creature()
{
	setArmor(0);
	setStrength(0);
	setName("");
}
/*********************************************************************
** Description: This is the overloaded constructor which initializes the
** name, armor, and strength from a derived class.
*********************************************************************/
Creature::Creature(const int armor, const int strength, string creatureName)
{
	setArmor(armor);
	setStrength(strength);
	setName(creatureName);
	cout << "Creature: " << creatureName << " created." << endl;
}
/*********************************************************************
** Description: This is a overloaded operator that receives both creatures
** that are currently fighting (right is attacking left) and returns back 
** the new strength of the creature who is receiving the attack (left).
** The code also takes into consideration of Medusa and the Vampire in
** regard to using their special abilities.
*********************************************************************/
int operator-(Creature &left, Creature &right) 
{
	int attack = right.getAttack();
	int defense = left.getDefense();
	int damage = (attack - defense) - left.getArmor();
	// Medusa's ability
	if (attack == 21)
	{
		cout << left.getName() << " has been turned into stone and has been defeated!" << endl;
		return left.getStrength();
	}
	// Vampire's ability
	else if (defense == 22)
	{
		cout << right.getName() << " has been charmed into not attacking!" << endl;
		return 0;
	}
	// If the damage inflicted is negative, return 0
	if (damage > 0)
	{
		// Returns the new strength value of the creature that got attacked
		return damage;
	}
	else
		return 0;
	// The new strength point is sent back to the creature that attacked
}
void Creature::setArmor(const int armor) 
{
	this->armor = armor;
}
void Creature::setStrength(const int strength)
{
	this->strength = strength;
}
void Creature::setName(const string creatureName)
{
	this->creatureName = creatureName;
}
int Creature::getArmor()
{
	return armor;
}
int Creature::getStrength()
{
	return strength;
}
string Creature::getName()
{
	return creatureName;
}