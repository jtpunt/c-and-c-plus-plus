/*********************************************************************
** Author: Jonathan Perry
** Date: 4/23/2017
** Description: This file contains the implentation code of the
** variables and functions needed for returning a random integer
** from 1 to the max number of sides to represent the rolling of die.
*********************************************************************/
#include "Die.hpp"
#include <cstdlib>
/*********************************************************************
** Description: This is a function operator that receives an integer which
** represents the max number of sides on a die and returns a random number
** between 1 and the max number of sides.
*********************************************************************/
int Die::operator() (int n)
{
	N = n;
	return ((rand() % (N - 1 + 1)) + 1);
}