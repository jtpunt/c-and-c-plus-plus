/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the class specifications of the
** variables and functions needed for creating the two creatures objects
** and sending them to fight each other.
*********************************************************************/
#ifndef PLAYGAME_HPP
#define PLAYGAME_HPP
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "Medusa.hpp"
#include "HarryPotter.hpp"
#include "Queue.hpp"
#include "LinkedList.hpp"
#include <vector>
#include <memory>
#include <string>
class PlayGame
{
private:
	// Stores both creatures so that their specific virtual functions may be called
	//std::vector<std::shared_ptr<Creature>> myCreatures;
	int numOfRounds = 0; // incremented by 1 each round
	int team1_wins = 0;
	int team2_wins = 0;
	std::string creature_name_team1;
	std::string creature_name_team2;
	Queue team1;
	Queue team2;
	LinkedList loserList;
	std::shared_ptr<Creature> team1_creature_ptr;
	std::shared_ptr<Creature> team2_creature_ptr;
public:
	PlayGame(std::vector<int>, std::vector<int>);
	void createCreatures(int, int);
	void startGame();
	void nextRound();
	void determineWinner();
};
#endif // !PLAYGAME
