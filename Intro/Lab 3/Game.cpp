/*********************************************************************
** Author: Jonathan Perry
** Date: 4/23/2017
** Description: This file contains the implentation code of the
** variables and functions needed to record the number of rounds
** to play, what type of die (loaded or regular die) to use, the number of 
** sides on their die each player is using, the amount of wins each 
** player has, and the rolls each individual user had each round.
*********************************************************************/
#include "Game.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using std::cout;
using std::endl;
using std::setw;
using std::cin;
/*********************************************************************
** Description: This is the default constructor which calls the menu to
** be displayed when an object is created.
*********************************************************************/
Game::Game()
{
	menu();
}
/*********************************************************************
** Description: This is a destructor that thanks the user after the 
** program exits.
*********************************************************************/
Game::~Game()
{
	cout << "\nThank you using my program!" << endl;
}
/*********************************************************************
** Description: This is a function that resets any error flags for cin
** and resets the input buffer.
*********************************************************************/
void Game::correctInput()
{
	// resets any error flags for cin if anything but integers are entered
	cin.clear();
	// Discards up to 1,000 characters from the input buffer or until a newline is read
	cin.ignore(1000, '\n');
	cout << "Please enter a non-negative integer: ";
}
/*********************************************************************
** Description: This is a function that displays the main program menu
** that calls other member functions to set the number of rounds
** to play, to set the specifications of both players individual die,
** execute the program, and exit the program.
*********************************************************************/
void Game::menu()
{
	system("clear"); // Clear the console screen
	int menuChoice;
	cout << "____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Set the number of rounds to play:               " << setw(7) << (choice1 ? "SET" : "NOT SET") << "|" << endl;
	cout << "|2. Set the dice type and its number of sides:      " << setw(7) << (choice2 ? "SET" : "NOT SET") << "|" << endl;
	cout << "|3. Run the program:                                       |" << endl;
	cout << "|4. Exit:                                                  |" << endl;
	cout << "|NOTE: To run the program, numbers 1-2 must be set         |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: "; 
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		choice1 = setNumberOfRounds();
		menu();
		break;
	case 2:
		setNumberOfSides(); // player 1
		choice2 = setNumberOfSides(); // player 2
		menu();
		break;
	case 3:
		if (choice1 && choice2)
		{
			start();
		}
		else
			menu();
		break;
	case 4:
		exit;
		break;
	default:
		cout << "Invalid input entered, please try again: " << endl;
		menu();
		break;
	}
}
/*********************************************************************
** Description: This is a function that asks the user to enter in the
** number of rounds to be played and stores their input
*********************************************************************/
bool Game::setNumberOfRounds()
{
	cout << "Number of rounds to play: ";
	cin >> numOfRounds;
	while (!cin)
	{
		correctInput();
		cin >> numOfRounds;
	}
	return true;
}
/*********************************************************************
** Description: This is a secondary menu that prompts both players to enter 
** the specifications of their die that their using. Specifications include:
**		- The number of sides on their die
**      - Loaded or regular die (loaded has a higher chance of
**        rolling a higher number)
*********************************************************************/
bool Game::setNumberOfSides()
{
	system("clear"); // Clear the console screen
	int menuChoice;
	cout << "____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Number of sides for player " << (currentPlayer ? 2 : 1) << ":" << setw(26) << (choice5 ? "SET" : "NOT SET") << "|" << endl;
	cout << "|" << setw(59) << "|" << endl;
	cout << "|2. Regular or loaded dice for player " << (currentPlayer ? 2 : 1) << ":" << setw(19) << (choice6 ? "SET" : "NOT SET") << "|" << endl;
	cout << "|" << setw(59) << "|" << endl;
	cout << "|NOTE: To return to main menu, numbers 1-2 must be set     |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		cout << "Enter the number of sides for player " << (currentPlayer ? 2 : 1) << ": ";
		if (currentPlayer) // False = player 1, true = player 2
			cin >> player2_NumOfSides;
		else
			cin >> player1_NumOfSides;
		while (!cin)
		{
			correctInput();
			if (currentPlayer) // False = player 1, true = player 2
				cin >> player2_NumOfSides;
			else
				cin >> player1_NumOfSides;
		}
		/* Set to true so that the menu changes from 'NOT SET' to 'SET'
		   Set to true so that the dice type can be set */
		choice5 = true;
		// Return to the secondary menu to enter dice type to be used for both players
		setNumberOfSides();
		break;
	case 2:
		/* Only allow dice type to be entered if the number of die sides has been entered
		   by the current player */
		if (choice5)
		{
			cout << "Do you want to use regular or loaded dice? " << endl;
			cout << "	- Enter 0 to use regular dice:" << endl;
			cout << "	- Enter 1 to use loaded dice: ";
			if (currentPlayer) // False = player 1, true = player 2
				cin >> player2_loadedDie;
			else
				cin >> player1_loadedDie;
			while (!cin)
			{
				correctInput();
				if (currentPlayer) // False = player 1, true = player 2
					cin >> player2_loadedDie;
				else
					cin >> player1_loadedDie;
			}
			choice5 = false; // Set to false before proceeding to ask the next player
			choice6 = false;
			currentPlayer = !(currentPlayer); // Switch to the next player
		}
		else
			// Return the current player back to the secondary menu
			setNumberOfSides();
		break;
	default:
		cout << "Invalid input entered, please try again: " << endl;
		setNumberOfSides();
		break;
	}
	return true;
}
/*********************************************************************
** Description: This is a function that receives an integer that represents
** the players roll from creating either a LoadedDie object or
** Die object anonymously based on the players' die type every round
** and stores that integer in separate vectors for both players.
*********************************************************************/
void Game::start()
{
	for (int i = 0; i < numOfRounds; i++)
	{
		/* Check what type of die player 1 is using
		   to create and use an object from the correct
		   class anonymously */
		if (player1_loadedDie) // Loaded
		{
			int number = LoadedDie() (player1_NumOfSides);
			player1_Rolls.push_back(number);
		}
		else // Regular
		{
			int number = Die() (player1_NumOfSides);
			player1_Rolls.push_back(number);
		}
		/* Check what type of die player 2 is using
		to create and use an object from the correct
		class anonymously */
		if (player2_loadedDie) // Loaded
		{
			int number = LoadedDie() (player2_NumOfSides);
			player2_Rolls.push_back(number);
		}
		else // Regular
		{
			int number = Die() (player2_NumOfSides);
			player2_Rolls.push_back(number);
		}
		// Record the player with the higher roll if there is no draw
		determineWinner(player1_Rolls.at(i), player2_Rolls.at(i));
	}
	/* Displays each players' die specification, the
	rolls of every individual round from each player, who the
	winner was or if there was a draw that round, and finally displays the
	the final winner which is the player that had the most round wins*/
	displayResults();
}
/*********************************************************************
** Description: This is a function receives each players roll after 
** every round and records the player who had the higher roll when 
** there is no draw for the round. 
*********************************************************************/
void Game::determineWinner(int player1, int player2)
{
	if (player1 > player2)
	{
		player1_NumOfWins++;
	}
	else if (player2 > player1)
	{   
		player2_NumOfWins++;
	}
}
/*********************************************************************
** Description: This is a function that displays each players' die 
** specification, therolls of every individual round from each player, who 
** the winner was or if there was a draw that round, and finally displays the
** the final winner (which is the player that had the most round wins).
*********************************************************************/
void Game::displayResults()
{
	system("clear"); // Clear the console screen
	int index = 0;
	cout << setw(19) << "Player 1" << setw(10) << "Player 2" << endl;
	cout << setw(9) << "Dice Used" << " [" << setw(8) << (player1_loadedDie ? "Loaded" : "Regular");
	cout << "][" << setw(8) << (player2_loadedDie ? "Loaded" : "Regular") << "]" << setw(8) << endl;
	cout << setw(10) << "# of Sides[" << setw(8);
	cout << player1_NumOfSides << "][" << setw(8) << player2_NumOfSides << "]" << endl;
	for (auto i : player1_Rolls)
	{
		cout << "Roll #" << setw(4) << index + 1 << "[" << setw(8);
		cout << setw(8) << i << "][";
		cout << setw(8) << player2_Rolls.at(index) << "]";
		if (i > player2_Rolls.at(index))
		{
			cout << " Player 1 Won!" << endl;
		}
		else if (i < player2_Rolls.at(index))
		{
			cout << " Player 2 Won!" << endl;
		}
		else if (i == player2_Rolls.at(index))
		{
			cout << " Draw!" << endl;
		}
		index++;
	}
	cout << setw(10) << "Total Wins[" << setw(8);
	cout << player1_NumOfWins << "][" << setw(8) << player2_NumOfWins << "]";
	if (player1_NumOfWins > player2_NumOfWins)
	{
		cout << " Final Winner: Player 1" << endl;
	}
	else if (player1_NumOfWins < player2_NumOfWins)
	{
		cout << " Final Winner: Player 2" << endl;
	}
	else if (player1_NumOfWins == player2_NumOfWins)
	{
		cout << " Final Winner: Draw!" << endl;
	}
}

