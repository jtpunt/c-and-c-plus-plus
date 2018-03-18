/*********************************************************************
** Author: Jonathan Perry
** Date: 1/25/2017
** Description: This program asks for a name of a file and then reads
** a list of integers in the file, calculates the sum of those values,
** and finally writes that sum to a new file called "sum.txt".
*********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ifstream inputFile; // Creates input filestream object
	ofstream outputFile; // Creates output filestream object
	string fileName; // Stores name of the file that the user wishes to oepn
	int value = 0, // Stores values read from the text file
		total = 0; // Stores the sum of all values

	// Ask the user for the file name and store it in fileName
	cout << "Enter the name of the file you wish to open: ";
	cin >> fileName; 

	// Open the text file as specified by user
	inputFile.open(fileName);
	if (inputFile) // Check to see that the file exists
	{
		// Check to see if a value is read and store it in value if it's true
		while (inputFile >> value)
		{
			total += value; // Add the value to total
		}
		// Open and write to the new text file once reading the file is complete
		outputFile.open("sum.txt");
		outputFile << total; // Write sum of data to the text file
		outputFile.close(); // Close output file when done writing data
	}
	// Catch error if file doesn't exist.
	else
	{
		cout << "Could not access file." << endl;
	}
	inputFile.close(); // Close input file when done reading data
	return 0;
}