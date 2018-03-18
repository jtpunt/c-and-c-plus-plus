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
#include <vector>
#include <memory>
#include <string>
class PlayGame
{
private:
	// Stores both creatures so that their specific virtual functions may be called
	std::vector<std::shared_ptr<Creature>> myCreatures;
	int numOfRounds = 0; // incremented by 1 each round
public:
	PlayGame(std::string, std::string);
	void createCreatures(std::string);
	void startGame();
	void nextRound();
};
#endif // !PLAYGAME
