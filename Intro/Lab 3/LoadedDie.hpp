/*********************************************************************
** Author: Jonathan Perry
** Date: 4/23/2017
** Description: This header file defines the class specifications of
** variables and functions needed for returning a random integer
** from 1 to the max number of sides to represent the rolling of die.
** However, this die has a side that holds more weight and is more prone
** to being rolled
*********************************************************************/
#ifndef LOADEDDIE_HPP
#define LOADEDDIE_HPP
#include "Die.hpp"
#include <vector>
class LoadedDie : public Die
{
private:
	// Stores the new weight of the die
	std::vector <int> weightedRolls;
public:
	/* Function operator that return a random integer from 1 to the max 
	   number of sides on a die */
	int operator() (int);
};

#endif // !LOADEDDIE_HPP