/*********************************************************************
** Author: Jonathan Perry
** Date: 4/16/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for initializing an array to be 
** used for retrieving and updating the array's data for the purpose of
** implementing Langton's Ant.
*********************************************************************/
#ifndef BOARD_HPP
#define BOARD_HPP
enum LangtonsAnt { WHITE_SQUARE, BLACK_SQUARE, INVALID_MOVEMENT};
class Board {
private:
	// Pointer to array
	char **boardPtr;
	int X_COLUMNS;
	int Y_ROWS;
public:
	// Constructor that takes user input to initial custom array
	Board(int, int);
	// Deconstructor that de-allocates the array
	~Board();
	// Prints the current tictactoe board
	void print();
	// Records the occupation of the current square
	void recordMove(int , int , char ch);
	int getX() { return X_COLUMNS; };
	int getY() { return Y_ROWS; }
	/* Receives coordinates to square
	 and returns its color */
	LangtonsAnt getColor(int, int);
};
#endif // !BOARD_HPP