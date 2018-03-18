/*********************************************************************
** Author: Jonathan Perry
** Date: 4/23/2017
** Description: This header file defines the class specifications of 
** the variables and functions needed to record the number of rounds
** to play, what type of die (loaded or regular die) to use, the number of 
** sides on their die each player is using, the amount of wins each 
** player has, and the rolls each individual user had each round.
*********************************************************************/
#ifndef GAME_HPP
#define GAME_HPP
#include "Die.hpp"
#include "LoadedDie.hpp"
#include <vector>
class Game
{
private:
	/* Menu feature to initially display 'NOT SET' for false and then 'SET' for true 
	   after the rounds to be played have been set by the user and then after 
	   each players die specifications have been entered */
	bool choice1 = false, choice2 = false, choice3 = false;
	bool choice4 = false, choice5 = false, choice6 = false;
	bool currentPlayer = false; // false = player 1, true = player 2
	int numOfRounds; // Number of rounds to be played
	// Total number of wins for player 1
	int player1_NumOfWins, player2_NumOfWins;
	// Total number of sides entered by player 1
	int player1_NumOfSides, player2_NumOfSides;
	// false = Die, true = LoadedDie
	bool player1_loadedDie = false, player2_loadedDie = false;
	// Stores the rolls of every round for player 1
	std::vector <int> player1_Rolls;
	std::vector <int> player2_Rolls;
public:
	// Constructor that call the menu to be displayed
	Game();
	// Destructor that thanks the players after they complete the game
	~Game();
	// Resets any error flags for cin and resets the input buffer
	void correctInput();
	// Prints the menu for the current user
	void menu();
	// Prompts the user to enter the number of rounds to be played
	bool setNumberOfRounds();
	/* Secondary menu which prompts both players individually to enter their 
	   specifications on their individual die */
	bool setNumberOfSides();
	// Starts the game
	void start(); 
	/* Receives each players roll after every round and records the player 
	   who had the higher roll when there is no draw for the round. */
	void determineWinner(int, int);
	/* Displays each players' die specification, the
	   rolls of every individual round from each player, who the
	   winner was or if there was a draw that round, and finally displays the 
	   the final winner which is the player that had the most round wins*/
	void displayResults();
};
#endif // !GAME_HPP
