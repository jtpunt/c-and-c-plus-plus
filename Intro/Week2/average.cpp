/*********************************************************************
** Author: Jonathan Perry
** Date: 1/18/2017
** Description: This program asks for user input for 5 numbers and then
** outputs the average of those five numbers.
*********************************************************************/
#include <iostream>
using namespace std;

int main()
{
	double someNumber, totalNumber;
	totalNumber = 0; // used to hold the value for the sum of the five numbers

	cout << "Please enter five numbers." << endl;
	cin >> someNumber; // reads each number into someNumber variable
	totalNumber += someNumber; // adds each user input into totalNumber to find sum of the five numbers

	cin >> someNumber;
	totalNumber += someNumber;

	cin >> someNumber;
	totalNumber += someNumber;

	cin >> someNumber;
	totalNumber += someNumber;

	cin >> someNumber;
	totalNumber += someNumber;

	cout << "The average of those numbers is:\n" <<  (totalNumber / 5) << endl; //(totalNumber / 5) calculates the average of the five numbers

	return 0;
}	
