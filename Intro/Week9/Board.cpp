/*********************************************************************
** Author: Jonathan Perry
** Date: 3/8/2017
** Description: This file contains the implentation code of the
** variables and functions needed for displaying a tic-tac-toe
** board on to the console window, storing the locations of the players'
** moves, and showing the current status of the game.
*********************************************************************/
#include <iostream>
#include "Board.hpp"
using namespace std;
const int Y_ROWS = 3;
const int X_COLUMNS = 3;
/*********************************************************************
** Description: This is a constructor of the Board class which
** initializes the 3x3 array to being empty.
*********************************************************************/
Board::Board()
{
	boardPtr = new char*[Y_ROWS];
	for (int i = 0; i < Y_ROWS; i++)
	{
		boardPtr[i] = new char[X_COLUMNS];
	}
	/*boardPtr[3][3];*/
}
/*********************************************************************
** Description: This is a function that takes the x and y cordinates of 
** the move and the current player and returns true if the area is 
** available and records the new location.
*********************************************************************/
bool Board::makeMove(int y, int x, char currentPlayer)
{
	if (boardPtr[y][x] != 'x' && boardPtr[y][x] != 'o')
	{
		boardPtr[y][x] = currentPlayer;
		return true;
	}
	else
		cout << "That square is already taken" << endl;
		return false;
}
/*********************************************************************
** Description: This is a function that prints the current tictactoe 
** board.
*********************************************************************/
void Board::print()
{
	for (int y = 0; y < Y_ROWS; y++)
	{
		if (y == 0)
		{
			cout << "  0 1 2" << endl;
		}
		for (int x = 0; x < X_COLUMNS; x++)
		{
			if (x == 0)
			{
				cout << y;
			}
			if (!(boardPtr[y][x] == 'x' || boardPtr[y][x] == 'o'))
			{
				cout << " .";
			}
			else 
			{
				cout << " " << boardPtr[y][x];
			}
		}
		cout << "\n";
	}
}
/*********************************************************************
** Description: This is a function that determines the current status
** of the game in regard to which player won, if it was a draw, or
** if the game is still going and returns that result.
*********************************************************************/
GameStatus Board::gameState()
{
	GameStatus status = UNFINISHED;

	for (int index = 0; index < 3; index++)
	{
		if (boardPtr[index][0] == boardPtr[index][1] && boardPtr[index][1] == boardPtr[index][2]) // horizontal check
		{
			if (boardPtr[index][0] == 'x')
				status = X_WON;
			else if (boardPtr[index][0] == 'o')
				status = O_WON;
			return status;
		}
		else if (boardPtr[0][index] == boardPtr[1][index] && boardPtr[1][index] == boardPtr[2][index]) // vertical check
		{
			if (boardPtr[0][index] == 'x')
				status = X_WON;
			else if (boardPtr[0][index] == 'o')
				status = O_WON;
			return status;
		}
	}
	if (boardPtr[0][0] == boardPtr[1][1] && boardPtr[1][1] == boardPtr[2][2]) // diagonal check
	{
		if (boardPtr[0][0] == 'x')
			status = X_WON;
		else
			status = O_WON;
		return status;
	}
	else if (boardPtr[2][0] == boardPtr[1][1] && boardPtr[1][1] == boardPtr[0][2]) // diagonal check
	{
		if (boardPtr[2][0] == 'x')
			status = X_WON;
		else
			status = O_WON;
		return status;
	}
	else
		status = DRAW;
	return status;
}
