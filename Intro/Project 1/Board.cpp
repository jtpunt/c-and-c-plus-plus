/*********************************************************************
** Author: Jonathan Perry
** Date: 3/8/2017
** Description: This file contains the implentation code of the
** variables and functions needed for initializing an array to be used
** for retrieving and updating the array's data for the purpose of
** implementing Langton's Ant.
*********************************************************************/
#include <iostream>
#include <iomanip>
#include "Board.hpp"
using namespace std;
/*********************************************************************
** Description: This is a constructor of the Board class which
** initializes the user-specified array to being empty.
*********************************************************************/
Board::Board(int y, int x)
{
	Y_ROWS = y;
	X_COLUMNS = x;
	boardPtr = new char*[Y_ROWS];
	for (int i = 0; i < y; i++)
	{
		boardPtr[i] = new char[X_COLUMNS];
	}
	// Loop through array again
	for (int y = 0; y < Y_ROWS; y++)
	{
		for (int x = 0; x < X_COLUMNS; x++)
		{
		// Set every element of matrix to be a white square
			boardPtr[y][x] = ' ';
		}
	}
}
/*********************************************************************
** Description: This is the default destructor of the Board class
** which de-allocates the 2D array to avoid memory leaks.
*********************************************************************/
Board::~Board()
{
	cout << "Board array is now being deallocated." << endl;
	for (int i = 0; i < Y_ROWS; i++)
		delete[] boardPtr[i];
	delete[] boardPtr;
}
/*********************************************************************
** Description: This is a function that receives a character, and an
** and x/y coordinates to update the array with the character that was 
** sent.
*********************************************************************/
void Board::recordMove(int y, int x, char ch)
{
	boardPtr[y][x] = ch;
}
/*********************************************************************
** Description: This is a function that prints the 2D array with the 
** current characters that are stored within it.
*********************************************************************/
void Board::print()
{
	// Loop through each element of the 2D array
	int i = 0;
	cout << "  ";
	// Prints out the x coordinates above the square matrix
	while (i < X_COLUMNS)
	{
		cout << setw(3) << i;
		i++;
	}
	cout << setw(3) << "x" << endl;
	for (int y = 0; y < Y_ROWS; y++)
	{
		cout << setw(2) << y << " ";
		for (int x = 0; x < X_COLUMNS; x++)
		{
			if (boardPtr[y][x] == ' ')
			{
				cout << "[ ]";
			}
			else
			{
				cout << "[" << boardPtr[y][x] << "]";
			}
			if (x == (X_COLUMNS - 1))
			{
				cout << "\n";
			}
		}
	}
	cout << setw(2) << "y" << endl;
}
/*********************************************************************
** Description: This is a function that receives x/y coordinates
** to determine and return the color of the position in question.
*********************************************************************/
LangtonsAnt Board::getColor(int y, int x)
{
	LangtonsAnt status;

	if (y > getY() - 1)
	{
		status = INVALID_MOVEMENT;
		return status;
	}
	else if (x > getX() - 1)
	{
		status = INVALID_MOVEMENT;
		return status;
	}
	else if (y < 0)
	{
		status = INVALID_MOVEMENT;
		return status;
	}
	else if (x < 0)
	{
		status = INVALID_MOVEMENT;
		return status;
	}
	else if (boardPtr[y][x] == '#')
	{
		status = BLACK_SQUARE;
		return status;
	}
	else if (boardPtr[y][x] == ' ')
	{
		status = WHITE_SQUARE;
		return status;
	}
	else
		status = INVALID_MOVEMENT;
	return status;
}
