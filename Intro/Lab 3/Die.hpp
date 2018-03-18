/*********************************************************************
** Author: Jonathan Perry
** Date: 4/23/2017
** Description: This header file defines the class specifications of
** variables and functions needed for returning a random integer
** from 1 to the max number of sides to represent the rolling of die.
*********************************************************************/
#ifndef DIE_HPP
#define DIE_HPP
class Die 
{
protected:
	// Stores the max number of sides on the die
	int N;
public:
	/* Function operator that return a random integer from 1 to the max
	number of sides on a die */
	int operator() (int n);
}; 

#endif // !DIE_HPP
