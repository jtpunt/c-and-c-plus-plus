#include "HarryPotter.hpp"
#include <memory>
#include <cstdlib>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
/*********************************************************************
** Description: This is the default constructor which initializes the
** name, armor, and strength of the creature.
*********************************************************************/
HarryPotter::HarryPotter(string name) : Creature(0, 10, name)
{
	cout << "Harry Potter is ready to fight!" << endl;
}
/*********************************************************************
** Description: This is a virtual function that checks to see if 
** Harry Potter is dead in order to revive him.
*********************************************************************/
int HarryPotter::getStrength()
{
	if (this->strength <= 0)
	{
		Hogwarts();
	}
	return this->strength;
}
/*********************************************************************
** Description: This is a function that simulates the rolling of two
** 6 sided die and then returns the sum of both rolls to represent the
** damage inflicted to their opponent.
*********************************************************************/
int HarryPotter::getAttack()
{
	return (rand() % 6 + 1) + (rand() % 6 + 1);
}
/*********************************************************************
** Description: This is a function that simulates the rolling of two
** 6 sided die and then returns the sum of both rolls to represent their
** defense points.
*********************************************************************/
int HarryPotter::getDefense()     
{
	return (rand() % 6 + 1) + (rand() % 6 + 1);
}
/*********************************************************************
** Description: This is a function that revives Harry Potter after dying.
** The function checks to see if Harry Potter has already been revived, so
** that he doesn't keep getting revived after every death.
*********************************************************************/
void HarryPotter::Hogwarts()
{
	// Check to see if Harry has already been revived
	while (!revives)
	{
		cout << "Harry Potter is back from the dead and is stronger than ever!" << endl;
		this->setStrength(20);
		revives = !revives;
	}
	if (!revives)
	{
		cout << "Harry Potter can no longer revive, he's dead!" << endl;
	}
}
