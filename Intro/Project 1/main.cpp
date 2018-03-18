/*********************************************************************
** Author: Jonathan Perry
** Date: 4/9/2017
** Description: This file contains the main function which drives the
** program by using functions from Ant.hpp to implement a simulation
** of Langton's Ant.
*********************************************************************/
#include "Ant.hpp"
#include <iostream>
using namespace std;
int main()
{
	unsigned x_input;
	unsigned y_input;
	cout << "How many rows and columns do you want in your matrix?" << endl;
	cout << "Rows: ";
	cin >> x_input;
	while (!cin || x_input > 80)
	{
		// resets any error flags for cin if anything but characters are entered
		cin.clear();
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		cout << "Please enter a non-negative integer: (max = 80)";
		cin >> x_input;
	}
	cout << "Columns: "; 
	cin >> y_input;
	// Keep asking until they enter an integer
	while (!cin || y_input > 80)
	{
		// resets any error flags for cin if anything but characters are entered
		cin.clear();
		// Discards up to 1,000 characters from the input buffer or until a newline is read
		cin.ignore(1000, '\n');
		cout << "Please enter a non-negative integer: (max = 80)";
		cin >> y_input;
	}
	Ant newAnt(x_input, y_input);
}