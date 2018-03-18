/*********************************************************************
** Author: Jonathan Perry
** Date: 4/9/2017
** Description: This file contains the implentation code of the
** variables and functions needed for determining the determinant of a
** 2x2 or 3x3 array.
*********************************************************************/
#include "determinant.hpp"
#include <iostream>
using namespace std;
/*********************************************************************
** Description: This is the default constructor that takes both a pointer
** to a 2D array and an integer as the size of the matrix as variables
** to calculate and print out the determinant of a 2x2 or 3x3 array.
*********************************************************************/
determinant::determinant(int **arrayPtr, const int sizeOfMatrix)
{
	if (sizeOfMatrix == 2)
	{
		cout << "Determinant value for 2x2: ";
		cout << ((arrayPtr[0][0] * arrayPtr[1][1]) - (arrayPtr[0][1] * arrayPtr[1][0])) << endl;
	}
	else if (sizeOfMatrix == 3)
	{
		cout << "Determinant value for 3x3: ";
		cout << ((arrayPtr[0][0] * ((arrayPtr[1][1] * arrayPtr[2][2]) - (arrayPtr[1][2] * arrayPtr[2][1]))) -
			(arrayPtr[0][1] * ((arrayPtr[1][0] * arrayPtr[2][2]) - (arrayPtr[1][2] * arrayPtr[2][0]))) +
			(arrayPtr[0][2] * ((arrayPtr[1][0] * arrayPtr[2][1]) - (arrayPtr[1][1] * arrayPtr[2][0])))) << endl;
	}
}