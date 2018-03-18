/*********************************************************************
** Author: Jonathan Perry
** Date: 3/07/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for displaying a tic-tac-toe
** board on to the console window, storing the locations of the players'
** moves, and showing the current status of the game.
*********************************************************************/
#ifndef BOARD_HPP
#define BOARD_HPP
enum GameStatus { X_WON, O_WON, DRAW, UNFINISHED };
class Board {
private:
	// Pointer to 3x3 array
	char **boardPtr;
	//char boardPtr[3][3];
public:
	// Default Constructor to initialize 3x3 array to zero
	Board();
	// Prints the current tictactoe board
	void print();
	// Records the moves of the current player if that location is unoccupied
	bool makeMove(int, int, char);
	// Determines which player won, if it was a draw, or if the game is still going
	GameStatus gameState();

};

#endif // !BOARD_HPP