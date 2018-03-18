/*********************************************************************
** Author: Jonathan Perry
** Date: 4/23/2017
** Description: This file contains the implentation code of the
** variables and functions needed for returning a random integer
** from 1 to the max number of sides to represent the rolling of die.
** However, this die has a side that holds more weight and is more prone
** to being rolled
*********************************************************************/
#include "LoadedDie.hpp"
#include <cstdlib>
/*********************************************************************
** Description: This is a function operator that receives an integer which
** represents the max number of sides on a die and then determines which
** individual side will be more prone to being rolled and finally returns
** a random integer between 1 and the max number of sides based on those
** constraints set from the weighted die.
*********************************************************************/
int LoadedDie::operator() (int n)
{
	N = n;
	/* The largest possible number that can be rolled is set to be
       the individual side that is more prone to being rolled */
	for (int i = 0; i < N; i++)
	{
		// Stores each number from 1 to N in the vector
		weightedRolls.push_back(i + 1);
		/* Matches the incremented iteration with the highest number
		   on the die that is more prone to being rolled */
		if (i + 1 == N)
		{
			/* Stores the highest number that is most prone to being rolled twice 
			   into the vector */
			weightedRolls.push_back(N);
		}
	}
	// Stores the size of the vector
	int maxSize = weightedRolls.size() - 1;
	// Stores a random number from 1 to the size of the vector
	int index = rand() % maxSize + 1;
	/* Stores an integer received from the 
	   vector at the specified subscript */
	int number = weightedRolls[index];
	return number;
}