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
using std::vector;
using std::make_shared;
using std::shared_ptr;
using std::getline;
using std::cout;
using std::cin;
using std::endl;
/*********************************************************************
** Description: This is the default constructor which a vector of integers
** from both team's that represent their picks for their creatures. 
** Each value from the vectors is sent 1 at a time to the createCreatures
** function to instantiate the creature objects. This function also keeps
** the game going when both teams have a creature at the front of their
** queue.
*********************************************************************/
PlayGame::PlayGame(vector <int> team_1, vector <int> team_2)
{
	int k = 0;
	for (int i = 0; i < team_1.size(); i++)
	{
		createCreatures(team_1.at(i), team_2.at(i));
	}
	while (!(team1.isEmpty()) && !(team2.isEmpty()))
	{
		team1_creature_ptr = team1.getCreature();
		team2_creature_ptr = team2.getCreature();
		creature_name_team1 = team1_creature_ptr->getName();
		creature_name_team2 = team2_creature_ptr->getName();
		cout << "\nMatch #:" << ++k << endl;
		cout << "\nTeam 1: " << creature_name_team1 << endl;
		cout << "Versus: \n" << "Team 2: " << creature_name_team2 << endl;
		cout << "Creatures left in team 1's queue: " << endl;
		team1.displayQueue();
		cout << "Creatures left in team 2's queue: " << endl;
		team2.displayQueue();
		startGame();
	}
	determineWinner();
	team1.~Queue();
	team2.~Queue();
}
/*********************************************************************
** Description: This is a function that receives vectors of integers 
** from both teams to instantiate each creature object.
*********************************************************************/
void PlayGame::createCreatures(int creature1, int creature2)
{
	string name = "";
	cout << "\nTeam1: Please enter in a name for the";
	switch (creature1)
	{
	case 1:
		cout << " Vampire creature: ";
		cin >> name;
		team1.addBack(make_shared<Vampire>(name));
		break;
	case 2:
		cout << " Barbarian creature: ";
		cin >> name;
		team1.addBack(make_shared<Barbarian>(name));
		break;
	case 3:
		cout << " Blue Men creature: ";
		cin >> name;
		team1.addBack(make_shared<BlueMen>(name));
		break;
	case 4:
		cout << " Medusa creature: ";
		cin >> name;
		team1.addBack(make_shared<Medusa>(name));
		break;
	case 5:
		cout << " Harry Potter creature: ";
		cin >> name;
		team1.addBack(make_shared<HarryPotter>(name));
		break;
	default:
		cout << "Error adding creature" << endl;
		break;
	}
	cin.clear();
	cout << "\nTeam2: Please enter in a name for the";
	switch (creature2)
	{
	case 1:
		cout << " Vampire creature: ";
		cin >> name;
		team2.addBack(make_shared<Vampire>(name));
		break;
	case 2:
		cout << " Barbarian creature: ";
		cin >> name;
		team2.addBack(make_shared<Barbarian>(name));
		break;
	case 3:
		cout << " Blue Men creature: ";
		cin >> name;
		team2.addBack(make_shared<BlueMen>(name));
		break;
	case 4:
		cout << " Medusa creature: ";
		cin >> name;
		team2.addBack(make_shared<Medusa>(name));
		break;
	case 5:
		cout << " Harry Potter creature: ";
		cin >> name;
		team2.addBack(make_shared<HarryPotter>(name));
		break;
	default:
		cout << "Error adding creature" << endl;
		break;
	}
}
/*********************************************************************
** Description: This is a function that starts the game and shows each
** round between fights to the user. Once someone has been defeated,
** the results of the game are displayed to the user.
*********************************************************************/
void PlayGame::startGame()
{
	while (team1_creature_ptr->getStrength() > 0 && team2_creature_ptr->getStrength() > 0)
	{
		cout << "\nRound: " << numOfRounds + 1 << endl;
		// Creature 2 is attacking creature 1
		// Creature 1 is receiving the attack
		nextRound();
		numOfRounds++;
	}
	// Did both players die?
	if ((team1_creature_ptr->getStrength() < 0) && (team1_creature_ptr->getStrength() < 0))
	{
		cout << creature_name_team1 << " and " << creature_name_team2 << " tied." << endl;
		// Copy both players' creatures at the front of the queue and place them at the back of the queue
		loserList.addHead(move(team1_creature_ptr));
		loserList.addHead(move(team2_creature_ptr));
	}
	// Did player 1 survive?
	else if (team1_creature_ptr->getStrength() > 0)
	{
		cout << creature_name_team1 << " won." << endl;
		cout << creature_name_team2 << " lost." << endl;
		team1_wins++; // Increment the counter for player 1's number of wins
		// Copy player 1's creature at the front of the queue and place them at the back of the queue
		team1.addBack(team1_creature_ptr);
		// Adds a random number from 1 - 10 onto the creature's current strength value
		team1_creature_ptr->setStrength(team1_creature_ptr->getStrength() + team1_creature_ptr->restoreHealth());
		// Move player 2's creature to the list of creatures of both player 1 and player 2 creatures who lost
		loserList.addHead(move(team2_creature_ptr));
	}
	// Did player 2 survive?
	else if (team2_creature_ptr->getStrength() > 0)
	{
		cout << creature_name_team2 << " won." << endl;
		cout << creature_name_team1 << " lost." << endl;
		team2_wins++; // Increment the counter for player 2's number of wins
		// Copy player 2's creature at the front of the queue and place them at the back of the queue
		team2.addBack(team2_creature_ptr);
		// Adds a random number from 1 - 10 onto the creature's current strength value
		team2_creature_ptr->setStrength(team2_creature_ptr->getStrength() + team2_creature_ptr->restoreHealth());
		// Move player 1's creature to the list of creatures of both player 1 and player 2 creatures who lost
		loserList.addHead(move(team1_creature_ptr));
	}
	// Remove the creature from the front of the queue so that the next creatures in queue can fight
	team1.removeFront();
	team2.removeFront();
	//THIS IS WHERE THE PROGRAM BREAKS!!
}
/*********************************************************************
** Description: This is a function that starts the game and simulates
** two creatures fighting each other. First, creature 2 attacks creature 1,
** and if creature 1 is still alive, creature 1 attacks creature 2.
*********************************************************************/
void PlayGame::nextRound()
{
	int damage = 0;
	cout << creature_name_team1 << " has " << team1_creature_ptr->getStrength() << " strength and " << team1_creature_ptr->getArmor() << " armor before the attack!" << endl;
	damage = *team1_creature_ptr - *team2_creature_ptr; // Simulate creature 2 attacking creature 1
	cout << creature_name_team1 << " took " << damage << " damage from " << creature_name_team2 << "!" << endl;
	cout << creature_name_team1 << " has " << team1_creature_ptr->getStrength() << " strength left!" << endl;

	if (team1_creature_ptr->getStrength() <= 0) // See if creature 1 is still alive
	{
		cout << creature_name_team1 << " has been defeated!" << endl;
	}
	else // Creature 1 is still alive
	{
		cout << creature_name_team2 << " has " << team2_creature_ptr->getStrength() << " strength and " << team2_creature_ptr->getArmor() << " armor before the attack!" << endl;
		damage = *team2_creature_ptr - *team1_creature_ptr; // Simulate creature 1 attacking creature 2
		cout << creature_name_team2 << " took " << damage << " damage from " << creature_name_team1 << "!" << endl;
		cout << creature_name_team2 << " has " << team2_creature_ptr->getStrength() << " strength left!" << endl;
	}
}
/*********************************************************************
** Description: This is a function that displays which team had more
** victories than the other, or in some cases if there was a tie between
** both teams. Finallly, a list of creatures who lost on both teams 
** is displayed.
*********************************************************************/
void PlayGame::determineWinner()
{
	cout << "\nTeam 1 had " << team1_wins << " victories." << endl;
	cout << "Team 2 had " << team2_wins << " victories." << endl;
	if (team1_wins == team2_wins)
	{
		cout << "Tie!" << endl;
	}
	else if (team1_wins > team2_wins)
	{
		cout << "Team 1 won!" << endl;
	}
	else if (team1_wins < team2_wins)
	{
		cout << "Team 2 won!" << endl;
	}
	cout << "\nHere is a list of creatures that lost on both team 1 and team 2." << endl;
	loserList.displayList();
}
	 

