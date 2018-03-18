/*********************************************************************
** Author: Jonathan Perry
** Date: 3/8/2017
** Description: This file contains the implentation code of the
** variables and functions needed for starting a game of Tic-Tac-Toe, 
** keeping track of whose turn it is and then asking that user 
** for their next move.
*********************************************************************/
#include "TicTacToe.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
/*********************************************************************
** Description: This is the default constructor of the TicTacToe class 
** which takes a char parameter that specifies whether 'x' or 'o' 
** should have the first move.
*********************************************************************/
TicTacToe::TicTacToe(char c)
{
	if (c == 'x')
		playersTurn = true;
	else
		playersTurn = false;
}
/*********************************************************************
** Description: This is the default destructor of the TicTacToe class
** which thanks the players after completing the game.
*********************************************************************/
TicTacToe::~TicTacToe()
{
	cout << "Thank you for playing!" << endl;
}
/*********************************************************************
** Description: This is a function that starts the game of tic-tac-toe
** and then outputs the current result of the game in regard to who won, 
** if it was a draw, or if the game is still going.
*********************************************************************/
void TicTacToe::play()
{
	for(int i = 0; i < 9; i++)
	{
	// Call this function to determine the current players' move
	currentTurn();
		// There can only be a winner after 5 moves have been made
		if (i > 3)
		{
        // Call the gameState member function to check the status of the game
		switch (board.gameState())
			{
			case X_WON:
				system("clear");
				board.print();
				cout << "\nX Won!" << endl;
				// Change the iteration of the for loop to end the game
				exit(0);
				break;
			case O_WON:
				system("clear");
				board.print();
				cout << "\n0 Won!" << endl;
				// Change the iteration of the for loop to end the game
				exit(0);
				break;
			case DRAW:
				cout << "Draw!" << endl;
				break;
			case UNFINISHED:
				cout << "Game is not complete!" << endl;
				break;
			}
		}
	}
}
/*********************************************************************
** Description: This is a function that keeps track of whose turn it is
** and then sends that players' moves to the board if they're valid and
** not already occupied.
*********************************************************************/
void TicTacToe::currentTurn()
{
	system("clear");
	// Stores the cordinates of the players' move
	int x, y;
	/* Stores the return value from Board member function makeMove
	   and is also initialized to false to start the while loop*/
	bool result = false;
	// Stores 'x' or 'o' based on the bool variable playersTurn
	char currentPlayer; 

	if (playersTurn)
		currentPlayer = 'x';
	else
		currentPlayer = 'o';

	board.print();
	
	// Ask the user to reenter their move until they pick an unoccupied location
	while (!result)
	{
		do
		{
		cout << "\n\nPlayer " << currentPlayer << ": please enter your move." << endl;
		cin >> y >> x;
			if (!((x == 0 || x == 1 || x == 2) && (y == 0 || y == 1 || y == 2)))
			cout << "Please enter 0, 1, or 2." << endl;
			// resets any error flags for cin if anything but integers are entered
			cin.clear();
			// Discard up to 1,000 characters from the input buffer or until a newline is read
			cin.ignore(1000, '\n');
		} 
		// Ask the user to input their move until it is 0, 1, or 2
		while (!((x == 0 || x == 1 || x == 2) && (y == 0 || y == 1 || y == 2)));
		// Send the cordinates and 'x' or 'o' to store their move
		result = board.makeMove(y, x, currentPlayer);
	}
	// Switch to the other player. 
	playersTurn = !playersTurn;
}

int main()
{
	char ch[2]; // store 'x' or 'o' character and '\0'
	char ch1; // Stores only 'x' or 'o'
	cout << "Which player goes first? (x or o)" << endl;
	cin >> ch;
	// Keep asking until they enter a single character that's just 'x' or 'o'
	while (ch[0] != 'x' && ch[0] != 'o' || strlen(ch) > 2)
	{
		// resets any error flags for cin if anything but characters are entered
		cin.clear();
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		cout << "Please enter (x or o):" << endl;
		cin >> ch;
	}
	ch1 = ch[0];
	system("clear");
	TicTacToe game1(ch1);
	game1.play();
}