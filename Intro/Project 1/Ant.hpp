/*********************************************************************
** Author: Jonathan Perry
** Date: 4/17/2017
** Description: This header file defines the class specifications of 
** the variables and functions needed for starting the simulation of Langton's
** Ant, determing what position the Ant is facing and the next position
** that the Ant will go to.
*********************************************************************/
#ifndef ANT_HPP
#define ANT_HPP
#include "Board.hpp"
enum DirectionFacing { UP, LEFT, RIGHT, DOWN };
class Ant : public Board
{
private:
	bool choice1, choice2, choice3, choice4;
	bool currentColor; // true = white, false = black
	int numOfSteps; // Number of steps to be completed
	/* Records coordinates of square previously occupied by the ant 
	   to change the color of the s6quare */
	int previous_x, previous_y;
	int current_x, current_y;
	// Stores current relative position of the ant
	DirectionFacing status;
public:
	// Constructor that take x,y coordiates to 
	Ant(int x, int y) : Board(x, y) { menu(); }
	// Destructor that thanks the players after they complete the game
	~Ant();
	// Prints the menu for the current user
	void menu();
	bool setNumberOfMoves();
	bool setStartingCoord();
	bool setRelativePosition();
	// Starts the 
	void start(); 
	// 
	void getNextMove();
	//
	DirectionFacing getDirection();
};
#endif // !ANT_HPP
