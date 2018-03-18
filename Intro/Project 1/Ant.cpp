/*********************************************************************
** Author: Jonathan Perry
** Date: 4/17/2017
** Description: This file contains the implentation code of the
** variables and functions needed for starting the simulation of Langton's
** Ant, determing what position the Ant is facing and the next position
** that the Ant will go to.
*********************************************************************/
#include "Ant.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
/*********************************************************************
** Description: This is the default destructor of the Ant class
** which thanks the user after completing the game.
*********************************************************************/
Ant::~Ant()
{
	cout << "Thank you using my program!" << endl;
}
/*********************************************************************
** Description: This is a menu function that allows the current user
** running the program to call other functions within the Ant class
** to set the starting coordinates, number of steps, and the relative 
** position of the Ant.
*********************************************************************/
void Ant::menu()
{
	system("clear"); // Clear the console screen
	int menuChoice;
	cout << "____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Set the number of moves for the ant to make:    " << setw(7) << (choice1 ? "SET" : "NOT SET") << "|" << endl;
	cout << "|2. Set the relative position of the ant:           " << setw(7) << (choice2 ? "SET" : "NOT SET") << "|" << endl;
	cout << "|3. Randomly set or input the starting coordinates: " << setw(7) << (choice3 ? "SET" : "NOT SET") << "|" << endl;
	cout << "|4. Run the program:                                       |" << endl;
	cout << "|5. Exit:                                                  |" << endl;
	cout << "|NOTE: To run the program, numbers 1-3 must be set         |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: "; 
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		choice1 = setNumberOfMoves();
		menu();
		break;
	case 2:
		choice2 = setRelativePosition();
		menu();
		break;
	case 3:
		choice3 = setStartingCoord();
		menu();
		break;
	case 4:
		if (choice1 && choice2 && choice3)
		{
			start();
		}
		else
			menu();
		break;
	case 5:
		exit;
		break;
	default:
		cout << "Invalid input entered, please try again: " << endl;
		menu();
	}
}
/*********************************************************************
** Description: This is a function that sets the number of movements
** that the Ant will take.
*********************************************************************/
bool Ant::setNumberOfMoves()
{
	cout << "Number of total moves (steps) for the ant to make: ";
	cin >> numOfSteps;
	while (!cin)
	{
		// resets any error flags for cin if anything but integers are entered
		cin.clear();
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		cout << "Please enter a non-negative integer: ";
		cin >> numOfSteps;
	}
	return true;
}
/*********************************************************************
** Description: This is a function that sets the first coordinates for
** the Ant to start at, which is chosen by the current user who is running
** the program.
*********************************************************************/
bool Ant::setStartingCoord()
{
	int choice;
	cout << "How do you want to set the starting coordinates?" << endl;
	cout << "1. Manually enter coordinates" << endl;
	cout << "2. Generate random numbers" << endl;
	cin >> choice;
	while (!cin || choice > 2 || choice < 1)
	{
		// resets any error flags for cin if anything but characters are entered
		cin.clear();
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		cout << "Please enter 1 or 2: ";
		cin >> choice;
	}
	if (choice == 1)
	{
		print();
		cout << "Enter coordinates of where the ant will start (e.g. 20 10): ";
		cin >> current_x >> current_y;
		// Keep asking until they enter 
		while (!cin || current_x > getX() - 1 || current_y > getY() - 1)
		{
			// resets any error flags for cin if anything but integer are entered
			cin.clear();
			// Discards up to 1,000 characters from the input buffer or until a newline is read
			cin.ignore(1000, '\n');
			cout << "Please enter a non-negative integer: ";
			cin >> current_x >> current_y;
		}
	}
	else 
	{
		srand(time(0));
		current_x = (rand() % ((getX() - 1) - 0 + 1)) + 0;
		current_y = (rand() % ((getY() - 1) - 0 + 1)) + 0;
	}
	return true;
	menu();
}
/*********************************************************************
** Description: This is a function that records the first direction
** the ant is facing, which is picked out by the current user who is 
** running the program.
*********************************************************************/
bool Ant::setRelativePosition()
{
	int numEntered;
	cout << "What direction will the ant be facing?" << endl;
	cout << "1. Up" << endl;
	cout << "2. Down" << endl;
	cout << "3. Left" << endl;
	cout << "4. Right" << endl;
	cout << "Enter a number: ";
	cin >> numEntered; 
	// Keep asking until they enter an integer
	while (!cin || numEntered > 4 || numEntered < 1)
	{
		// resets any error flags for cin if anything but integer are entered
		cin.clear();
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		cout << "What direction will the ant be facing?" << endl;
		cout << "1. Up" << endl;
		cout << "2. Down" << endl;
		cout << "3. Left" << endl;
		cout << "4. Right" << endl;
		cout << "Please enter 1, 2, 3, or 4:" << endl;
		cin >> numEntered;
	}
	if (numEntered == 1)
		status = UP;
	else if (numEntered == 2)
		status = DOWN;
	else if (numEntered == 3)
		status = LEFT;
	else if (numEntered == 4)
		status = RIGHT;
	return true;
	menu();
}
/*********************************************************************
** Description: This is a function that starts the simulation of Langton's
** Ant, keeps count of each iteration, and flips the colors of the squares.
*********************************************************************/
void Ant::start()
{
	/* Initialized previous coordinates to 
	   user-specified starting point */
	previous_y = current_y;
	previous_x = current_x;
	for (int i = 0; i < numOfSteps; i++)
	{
		if (currentColor) // white
		{
			// switch square color to black
			recordMove(previous_y, previous_x, '#');
		}
		else if (!currentColor) // black
		{
			// switch square color to white
			recordMove(previous_y, previous_x, ' ');
		}
		cout << "\nMove number: " << i + 1 << endl;
		cout << "Current x: " << current_x << endl;
		cout << "Current y: " << current_y << endl;
		getNextMove();
	}
	cout << "\nFinal board:" << endl;
	print();
}
/*********************************************************************
** Description: This is a function that implements the rules regarding
** Langton's Ant. That is: 
** 1. In a white square, turn right 90 degrees, change the square 
**    to black and move forward one unit.
** 2. In a black square, turn left 90 degrees, change the square to 
**    white and move forward one unit.
*********************************************************************/
void Ant::getNextMove()
{
	// Retrieve the relative direction the ant is facing
	switch (getDirection())
	{
	case RIGHT:
		/* Retieve the current color of the square
		   by calling getColor - member function of the 
		   Board class */
		switch (getColor(current_y, current_x))
		{
		case WHITE_SQUARE:
			// Send ant to current x/y coordinates
			recordMove(current_y, current_x, '@');
			/* Record coordinates to change the color
			of the square in next loop */
			// Increment y to move ant down in next loop
			previous_y = current_y++;
			previous_x = current_x;
			// true because the current square is white
			currentColor = true;
			// Relative position of the ants' next move
			status = DOWN;
			break;
		case BLACK_SQUARE:
			// Send ant to current x/y coordinates
			recordMove(current_y, current_x, '@');
			/* Record coordinates to change the color
			of the square in next loop */
			// Decrement y to move ant up in next loop
			previous_y = current_y--;
			previous_x = current_x;
			// false because the current square is black
			currentColor = false;
			// Relative position of the ants' next move
			status = UP;
			break;
		case INVALID_MOVEMENT:
			cout << "Out of bounds error: Placing the ant on the opposite side." << endl;
			cout << "The '@' will be visible on the board with the next move." << endl;
			previous_x = current_x - 1;
			current_x = 0;
			status = RIGHT;
			break;
		}
		break;
	case LEFT:
		/* Retieve the current color of the square
		by calling getColor - member function of the
		Board class */
		switch (getColor(current_y, current_x))
		{
		case WHITE_SQUARE:
			// Send ant to current x/y coordinates
			recordMove(current_y, current_x, '@');
			/* Record coordinates to change the color
			of the square in next loop */
			// Decrement y to move ant up in next loop
			previous_y = current_y--;
			previous_x = current_x;
			// true because the current square is white
			currentColor = true;
			// Relative position of the ants' next move
			status = UP;
			break;
		case BLACK_SQUARE:
			// Send ant to current x/y coordinates
			recordMove(current_y, current_x, '@');
			/* Record coordinates to change the color
			of the square in next loop */
			// Increment y to move ant down in next loop
			previous_y = current_y++;
			previous_x = current_x;
			// false because the current square is black
			currentColor = false;
			// Relative position of the ants' next move
			status = DOWN;
			break;
		case INVALID_MOVEMENT:
			cout << "Out of bounds error: Placing the ant on the opposite side." << endl;
			cout << "The '@' will be visible on the board with the next move." << endl;
			previous_x = current_x + 1;
			current_x = getX() - 1;
			status = LEFT;
			break;
		}
		break;
	case UP:
		/* Retieve the current color of the square
		by calling getColor - member function of the
		Board class */
		switch (getColor(current_y, current_x)) // What is the current square we are on?
		{
		case WHITE_SQUARE:
			// Send ant to current x/y coordinates
			recordMove(current_y, current_x, '@');
			/* Record coordinates to change the color
			of the square in next loop */
			// Increment x to move ant right in next loop
			previous_x = current_x++;
			previous_y = current_y;
			// true because the current square is white
			currentColor = true;
			// Relative position of the ants' next move
			status = RIGHT;
			break;
		case BLACK_SQUARE:
			// Send ant to current x/y coordinates
			recordMove(current_y, current_x, '@');
			/* Record coordinates to change the color
			of the square in next loop */
			// Decrement x to move ant left in next loop
			previous_x = current_x--;
			previous_y = current_y;
			// false because the current square is black
			currentColor = false;
			// Relative position of the ants' next move
			status = LEFT;
			break;
		case INVALID_MOVEMENT:
			cout << "Out of bounds error: Placing the ant on the opposite side." << endl;
			cout << "The '@' will be visible on the board with the next move." << endl;
			previous_y = current_y + 1;
			current_y = getY() - 1;
			status = UP;
			break;
		}
		break;
	case DOWN:
		/* Retieve the current color of the square
		by calling getColor - member function of the
		Board class */
		switch (getColor(current_y, current_x))
		{
		case WHITE_SQUARE:
			// Send ant to current x/y coordinates
			recordMove(current_y, current_x, '@');
			/* Record coordinates to change the color
			of the square in next loop */
			// Decrement x to move ant left in next loop
			previous_x = current_x--;
			previous_y = current_y;
			// true because the current square is white
			currentColor = true;
			// Relative position of the ants' next move
			status = LEFT;
			break;
		case BLACK_SQUARE:
			// Send ant to current x/y coordinates
			recordMove(current_y, current_x, '@');
			/* Record coordinates to change the color
			of the square in next loop */
			// Decrement x to move ant right in next loop
			previous_x = current_x++;
			previous_y = current_y;
			// false because the current square is black
			currentColor = false;
			// Relative position of the ants' next move
			status = RIGHT;
			break;
		case INVALID_MOVEMENT:
			cout << "Out of bounds error: Placing the ant on the opposite side." << endl;
			cout << "The '@' will be visible on the board with the next move." << endl;
			previous_y = current_y - 1;
			current_y = 0;
			status = DOWN;
			break;
		}
		break;
	}
	print();
}
/*********************************************************************
** Description: This is a function that returns the current direction
** that the ant is facing.
*********************************************************************/
DirectionFacing Ant::getDirection()
{
	return status;
}

