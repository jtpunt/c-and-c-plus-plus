/*********************************************************************
** Author: Jonathan Perry
** Date: 4/9/2017
** Description: This header file defines the class specifications of
** variables and functions needed for dynamically allocating space for
** a 2D array, prompting a user to fill a square matrix and storing
** that user input into the 2D array.
*********************************************************************/
#ifndef readMatrix_HPP
#define readMatrix_HPP
class readMatrix {
private:
	// Pointer to 2D array
	int **matrixPtr;
	int sizeOfMatrix;
public:
	// Default Constructor to initialize 2x2 or 3x3 array to zero
	readMatrix(int **, const int);
	// Displays the array (as a square)
	void print();
	// Gathers and stores input into 2D array
	void getInput();
};

#endif // !readMatrix_HPP