/*********************************************************************
** Author: Jonathan Perry
** Date: 4/9/2017
** Description: This file contains the main function which drives the 
** program by using functions from readMatrix.hpp and determininant.hpp
** to calculate the determinant of a 2x2 or 3x3 array from user-entered
** data.
*********************************************************************/
#include "readMatrix.hpp"
#include "determinant.hpp"
#include <iostream>
using namespace std;

int main()
{
	int sizeOfMatrix;
	int **ptrToMatrix = nullptr;
	cout << "What is the size of your matrix?" << endl;
	cout << "	- Enter 2 for 2x2 matrix:" << endl;
	cout << "	- Enter 3 for 3x3 matrix:" << endl;
	cin >> sizeOfMatrix;
	// Keep asking until they enter a single character that's just 'x' or 'o'
	while (sizeOfMatrix != 2 && sizeOfMatrix != 3)
	{
		// resets any error flags for cin if anything but characters are entered
		cin.clear();
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		cout << "Please enter (2 or 3):" << endl;
		cin >> sizeOfMatrix;
	}
	ptrToMatrix = new int*[sizeOfMatrix];
	readMatrix newMatrix(ptrToMatrix, sizeOfMatrix);
	newMatrix.print();
	determinant newDeterminant(ptrToMatrix, sizeOfMatrix);
	// Free up the dynamically allocated memory
	delete ptrToMatrix;
	ptrToMatrix = nullptr;
}