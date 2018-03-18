/*********************************************************************
** Author: Jonathan Perry
** Date: 3/07/2017
** Description: This header file defines the class specifications of 
** the variables and functions needed for starting a game of Tic-Tac-Toe, 
** keeping track of whose turn it is and then asking that user 
** for their next move.
*********************************************************************/
#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include "Board.hpp"
class TicTacToe {
private:
	Board board;
	bool playersTurn;
public:
	// Constructor that takes a char parameter that specifies whether 'x' or 'o' should have the first move
	TicTacToe(char c);
	// Destructor that thanks the players after they complete the game
	~TicTacToe();
	// Starts the game and continues until someone has won or it's a draw
	void play(); 
	// Asks the correct player for their move and sends it to the board
	void currentTurn();
};

#endif // !TICTACTOE_HPP
