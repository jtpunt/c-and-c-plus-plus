/*********************************************************************
** Author: Jonathan Perry
** Date: 4/9/2017
** Description: This file contains the implentation code of the
** variables and functions needed for dynamically allocating space for
** a 2D array, prompting a user to fill a square matrix and storing
** that user input into the 2D array.
*********************************************************************/
#include "readMatrix.hpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;
/*********************************************************************
** Description: This is a constructor that takes a pointer to a 2D array
** and an integer as the size of the matrix to dynamically allocate space
** for the 2D array and then prompts the user to enter integers by 
** calling the getInput function.
*********************************************************************/
readMatrix::readMatrix(int **arrayPtr, const int matrixSize)
{
	system("clear"); // Clear the console screen
	matrixPtr = arrayPtr; // Store the address of pointer passed
	/* Stored as private member variable 'sizeOfMatrix' to be 
	   be accessed by other functions from the same class. */
	sizeOfMatrix = matrixSize;
	// Dynamically allocate the space for the 2D array
	for (int i = 0; i < sizeOfMatrix; i++)
	{
		// Initialize according to dimensions of the array
		matrixPtr[i] = new int[sizeOfMatrix];
	}
	// Initialize every element of the 2D array to NULL
	for (int y = 0; y < sizeOfMatrix; y++)
	{
		for (int x = 0; x < sizeOfMatrix; x++)
		{
			matrixPtr[y][x] = 0;
		}
	}
	getInput(); // Gather and store user input
}
/*********************************************************************
** Description: This is a function that asks the user for input to fill
** the array with integer data.
*********************************************************************/
void readMatrix::getInput()
{
	int input; // Holds the user's input
	// Loop through each element of the 2D array
	for (int y = 0; y < sizeOfMatrix; y++)
	{
		for (int x = 0; x < sizeOfMatrix; x++)
		{
			print();
			cout << "Enter the next integer: ";
			cin >> input;
			while (!cin) // Reject incorrect data, ask again for input
			{
				system("clear");
				print();
				cout << "Invalid input entered: Please enter an integer" << endl;
				// resets any error flags for cin if anything but integers are entered
				cin.clear();
				// Discard up to 1,000 characters from the input buffer or until a newline is read
				cin.ignore(1000, '\n');
				cin >> input;
			}
			system("clear");
			matrixPtr[y][x] = input; // Store the input into the array
		}
	}
}
/*********************************************************************
** Description: This is a function that prints a 2x2 or 3x3 square with
** the current data that has been entered into the matrix.
*********************************************************************/
void readMatrix::print()
{
	// Determine dimensions of 2D matrix
	if (sizeOfMatrix > 2) // Check if 3x3 array
	{
		// Print top of the square out for a 3x3 array
		cout << "_______" << "_______" << "________" << endl;
	}
	else // Matrix is then a 2x2 array
	{
		// Print top of the square out for a 2x2 array
		cout << "_______" << "________" << endl;
	}
	// Loop through each element of the 2D array
	for (int y = 0; y < sizeOfMatrix; y++)
	{
		for (int x = 0; x < sizeOfMatrix; x++)
		{
			// Check that the element of the current subscript isn't NULL
			if (matrixPtr[y][x] == 0)
				// Print blank space instead of 0 (NULL)
				cout << "|" << setw(6) << " ";
			else
				// Print array's current subscript element when it's not NULL
				cout << "|" << setw(6) << matrixPtr[y][x];
			// Check to see if x is at the last column of the current row
			if (x == sizeOfMatrix - 1)
			{
				cout << "|" << endl;
				cout << "|______" << "|______|"; 
				// Check to see if matrix is a 3x3 array
				if (x > 1)
				{
					cout << "______|" << endl;
				}
				else
				{
					cout << "\n";
				}
			}
		}
	}
}