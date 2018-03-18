/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the implementation code of the 
** variables and functions needed for creating the two creatures objects
** and sending them to fight each other.
*********************************************************************/
#include "PlayGame.hpp"
#include "Creature.hpp"
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "Medusa.hpp"
#include "HarryPotter.hpp"
#include <iostream>
using std::string;
using std::make_shared;
using std::cout;
using std::endl;
/*********************************************************************
** Description: This is the default constructor which receives both
** creature names and sends them to the function createCreatures() to
** be created and stored in an array before starting the game.
*********************************************************************/
PlayGame::PlayGame(string creature1, string creature2)
{
	createCreatures(creature1);
	createCreatures(creature2);
	startGame();
}
/*********************************************************************
** Description: This is a function that receives the name of the creature
** to be created and stores that creature in an array.
*********************************************************************/
void PlayGame::createCreatures(string creature)
{
	if (creature == "vampire")
		myCreatures.push_back(make_shared<Vampire>());
	else if (creature == "barbarian")
		myCreatures.push_back(make_shared<Barbarian>());
	else if (creature == "blue men")
		myCreatures.push_back(make_shared<BlueMen>());
	else if (creature == "medusa")
		myCreatures.push_back(make_shared<Medusa>());
	else if (creature == "harry potter")
		myCreatures.push_back(make_shared<HarryPotter>());
}
/*********************************************************************
** Description: This is a function that starts the game and shows each
** round between fights to the user. Once someone has been defeated,
** the results of the game are displayed to the user.
*********************************************************************/
void PlayGame::startGame()
{
	while (myCreatures[0]->getStrength() > 0 && myCreatures[1]->getStrength() > 0)
	{
		cout << "\nRound: " << numOfRounds + 1 << endl;
		// Creature 2 is attacking creature 1
		// Creature 1 is receiving 
		nextRound();
		numOfRounds++;
	}
	if ((myCreatures[0]->getStrength() < 0) && (myCreatures[0]->getStrength() < 0))
	{
		cout << myCreatures[0]->getName() << " and " << myCreatures[1]->getName() << " both lost." << endl;
	}
	if(myCreatures[0]->getStrength() > 0)
	{
		cout << myCreatures[0]->getName() << " won." << endl;
		cout << myCreatures[1]->getName() << " lost." << endl;
	}
	else if (myCreatures[1]->getStrength() > 0)
	{
		cout << myCreatures[1]->getName() << " won." << endl;
		cout << myCreatures[0]->getName() << " lost." << endl;
	}
}
/*********************************************************************
** Description: This is a function that starts the game and simulates
** two creatures fighting each other. First, creature 2 attacks creature 1,
** and if creature 1 is still alive, creature 1 attack creature 2.
*********************************************************************/
void PlayGame::nextRound()
{
	int damage;
	cout << myCreatures[0]->getName() << " has " << myCreatures[0]->getStrength() << " strength and " << myCreatures[0]->getArmor() << " armor before the attack!" << endl;
	damage = *myCreatures[0] - *myCreatures[1]; // Simulate creature 2 attacking creature 1
	cout << myCreatures[0]->getName() << " took " << damage << " damage from " << myCreatures[1]->getName() << "!" << endl;
	myCreatures[0]->setStrength(myCreatures[0]->getStrength() - damage); // Set the new health of creature 1 after the attack
	cout << myCreatures[0]->getName() << " has " << myCreatures[0]->getStrength() << " strength left!" << endl;

	if (myCreatures[0]->getStrength() <= 0) // See if creature 1 is still alive
	{
		cout << myCreatures[0]->getName() << " has been defeated!" << endl;
	}
	else
	{
		cout << myCreatures[1]->getName() << " has " << myCreatures[1]->getStrength() << " strength and " << myCreatures[1]->getArmor() << " armor before the attack!" << endl;
		damage = *myCreatures[1] - *myCreatures[0]; // Simulate creature 1 attacking creature 2
		cout << myCreatures[1]->getName() << " took " << damage << " damage from " << myCreatures[0]->getName() << "!" << endl;
		myCreatures[1]->setStrength(myCreatures[1]->getStrength() - damage); // Set the new health of creature 2 after the attack
		cout << myCreatures[1]->getName() << " has " << myCreatures[1]->getStrength() << " strength left!" << endl;
	}
}