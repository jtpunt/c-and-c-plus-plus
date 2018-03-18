/*********************************************************************
** Author: Jonathan Perry
** Date: 1/25/2017
** Description: This program finds the minimum and maximum value of  
** numbers entered by the user and then displays them.
*********************************************************************/
#include <iostream>
using namespace std;

int main()
{
	int initialNumber, // The amount of integers to be entered
		inputNumber, // Current integer entered
		minNumber,
		maxNumber;

	cout << "How many integers would you like to enter?" << endl;
	cin >> initialNumber;

	// Outputs singular "integer" versus plural "integers" based on intialNumber
	if (initialNumber == 1)
	{
		cout << "Please enter " << initialNumber << " integer." << endl;
	}
	else
	{
		cout << "Please enter " << initialNumber << " integers." << endl;
	}

	cin >> inputNumber;
	/* Initialized both minNumber and maxNumber to inputNumber so
	that they can be compared to the initial number entered for inputNumber
	in the for loop. If minNumber was set to 0 and the user entered values > 0,
	then minValue would still be 0 and output for minimum would
	be incorrect. If maxNumber was set to 0 and the user entered values < 0,
	then maxValue would still be 0 and output for maximum would
	be incorrect.*/
	minNumber = inputNumber;
	maxNumber = inputNumber;

	/* Used to loop a number of times based on initialNumber, but
	   input has already been entered once, so we have to loop 1 less (intialNumber - 1)*/
	for (int i = 0; i < initialNumber - 1; i++)
	{
		cin >> inputNumber; // each loop asks for user input

		if (inputNumber > maxNumber) // each input compared to maxNumber
		{
			maxNumber = inputNumber; // maxNumber set to input when true
		}
		// each input compared to minNumber when first if statement is false
		else if (inputNumber < minNumber)
		{
			minNumber = inputNumber; // minNumber set to input when true
		}
	}
	// Display the minimum and maximum values
	cout << "min: " << minNumber << endl;
	cout << "max: " << maxNumber << endl;
}