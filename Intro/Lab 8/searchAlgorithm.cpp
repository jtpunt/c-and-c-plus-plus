/*********************************************************************
** Author: Jonathan Perry
** Date: 5/28/2017
** Description: This file contains the implementation code of the
** variables and functions needed for searching for a value in a text
** file through both a linear search algorithm and a binary search algorithm.
** After reading the text files for the first time, values from the files are 
** stored in 2 designated vectors (1 contains the original data, the other 
** vector contains the sorted integers) - which are both used to perform 
** the binary search. After the vectors are sorted, the program prompts
** the user to enter in the name of the output file they wish to save
** the sorted values into.
*********************************************************************/
#include "searchAlgorithm.hpp"
#include <iostream>
#include <fstream>
using std::fstream;
using std::ofstream;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
/*********************************************************************
** Description: This is a function that calls readFile for each of the 
** 4 files and returns true if the value is found, false if the value
** is not found in the files. The boolean result and the search value
** are then sent to the searchValueResults function to display the 
** search value and whether or not the value was found in the list.
*********************************************************************/
void searchAlgorithm::searchValue(int x)
{
	cout << "File 1 ";
	searchValueResults(readFile("original.txt", x, file1, originalFile1), x);
	cout << "\nFile 2 ";
	searchValueResults(readFile("early.txt", x, file2, originalFile2), x);
	cout << "\nFile 3 ";
	searchValueResults(readFile("middle.txt", x, file3, originalFile3), x);
	cout << "\nFile 4 ";
	searchValueResults(readFile("end.txt", x, file4, originalFile4), x);
}
/*********************************************************************
** Description: This is a function that receives the name of the file
** to be read, the value to be searched, and a reference to the vector
** to fill that vector with each data within the file. Each value in the
** file is also displayed to the user.
** CITE: Searching, Sorting, and Algorithm Analysis." Starting Out With C Early Objects.
**		 N.p.: Pearson College Div, 2016. N. pag. Print.
**       Page #: 612 Linear Search Example
*********************************************************************/
bool searchAlgorithm::readFile(string fileName, int searchValue, vector<int>& vector1, vector<int>& original)
{
	bool result = false; // False = no matching value found, true - match found
	fstream ioFile;
	int integer;
	ioFile.open(fileName);
	if (ioFile.fail())
	{
		cout << "The file failed to open: " << endl;
	}
	// While the file still has values to read
	while (ioFile >> integer)
	{
		// Did we find a match on the value we are searching for?
		if (searchValue == integer)
		{
			// Return true, we did find the value we were searching for
			result = true;
		}
		// Push the value obtained from the file into the designated vector
		vector1.push_back(integer);
		original.push_back(integer);
		cout << integer << " ";
	}
	cout << endl;
	return result; 
	ioFile.close(); // Close the file
}
/*********************************************************************
** Description: This is a function that receives the result of the search
** (e.g., the search value was found/ not found), and the search value
** and displays the search value and whether it was found or not in the
** file.
*********************************************************************/
void searchAlgorithm::searchValueResults(bool result, int searchValue)
{
	cout << "target value " << searchValue;
	if (result)
	{
		cout << " found" << endl;
	}
	else
	{
		cout << " not found" << endl;
	}
}
/*********************************************************************
** Description: This is a function that sends each vector of integers
** gather from each file to be sorted through a bubble sort algorithm.
** After sorting the vector, the vector is sent to the outputIntegers
** function to save a .txt file of the newly sorted vector.
*********************************************************************/
void searchAlgorithm::startSort()
{
	sortValues(file1);
	outputIntegers(file1);

	sortValues(file2);
	outputIntegers(file2);

	sortValues(file3);
	outputIntegers(file3);

	sortValues(file4);
	outputIntegers(file4);
}
/*********************************************************************
** Description: This is a function that receives a reference to a vector
** and then uses a bubble sort algorithm to sort the values of the
** vector.
** CITE: Searching, Sorting, and Algorithm Analysis." Starting Out With C Early Objects.
**		 N.p.: Pearson College Div, 2016. N. pag. Print.
**       Page #: 616 Bubble Sort Example
*********************************************************************/
void searchAlgorithm::sortValues(vector<int>& integers)
{
	int temp;
	bool madeAswap; // Keeps track of if a swap has been made
	do
	{
		madeAswap = false;
		for (int count = 0; count < integers.size() - 1; count++)
		{
			// Is the previous value greater than the next value over?
			if (integers[count] > integers[count + 1])
			{
				// Save the value to temp
				temp = integers[count];
				// Set the previous value equal to the next value over
				integers[count] = integers[count + 1];
				// Set the next value over equal to the value previous to it
				integers[count + 1] = temp;
				madeAswap = true;
			}
		}
	} while (madeAswap); // Loop back if a swap was made
}
/*********************************************************************
** Description: This is a function that receives a reference to a vector
** and then prompts the user to enter in a name of a file to save the
** sorted vectors into.
*********************************************************************/
void searchAlgorithm::outputIntegers(vector<int> integers)
{
	bool result = false;
	string fileName;
	int integer;

	cout << "What is the name of the file you wish to save the sorted integers as?" << endl;
	cin >> fileName;

	ofstream outFile(fileName);
	// See if the file is open
	if (outFile.is_open())
	{
		// Output the values to the file
		for (auto i : integers)
		{
			outFile << i << " ";
		}
	}
	// File is not open
	else
	{
		cout << "The file failed to open: " << endl;
	}
	outFile << endl;
	outFile.close(); // Close the file
}
/*********************************************************************
** Description: This is a function that starts the binary search algorithm
** on all 4 files (original and sorted) and then displays where the 
** element was found.
*********************************************************************/
void searchAlgorithm::startBinarySearch(int searchValue)
{
	cout << "\nThe value " << searchValue;
	binarySearchResults(binarySearch(originalFile1, searchValue));
	cout << " of the 1st original file 'original.txt'." << endl;
	cout << "The value " << searchValue;
	binarySearchResults(binarySearch(file1, searchValue)); 
	cout << " of the 1st sorted file 'original.txt'." << endl;


	cout << "\nThe value " << searchValue;
	binarySearchResults(binarySearch(originalFile2, searchValue));
	cout << " of the 2nd original file 'early.txt'." << endl;
	cout << "The value " << searchValue;
	binarySearchResults(binarySearch(file2, searchValue));
	cout << " of the 2nd sorted file 'early.txt'." << endl;


	cout << "\nThe value " << searchValue;
	binarySearchResults(binarySearch(originalFile3, searchValue));
	cout << " of the 3rd original file 'middle.txt'." << endl;
	cout << "The value " << searchValue;
	binarySearchResults(binarySearch(file3, searchValue));
	cout << " of the 3rd sorted file 'middle.txt'." << endl;


	cout << "\nThe value " << searchValue;
	binarySearchResults(binarySearch(originalFile4, searchValue));
	cout << " of the 4th original file 'end.txt'." << endl;
	cout << "The value" << searchValue;
	binarySearchResults(binarySearch(file4, searchValue));
	cout << " of the 4th sorted file 'end.txt'." << endl;
}
/*********************************************************************
** Description: This is a function that receives a vector of integers
** by value and also receives the value being searched and then finally
** returns the position of the searchValue where the element was found
** in the vector.
** CITE: Searching, Sorting, and Algorithm Analysis." Starting Out With C Early Objects.
**		 N.p.: Pearson College Div, 2016. N. pag. Print.
**       Page #: 608 Binary Search Example
*********************************************************************/
int searchAlgorithm::binarySearch(const vector<int> integers, int value)
{
	int first = 0,
		last = integers.size() - 1,
		middle,
		position = -1;
	bool found = false;
	while (!found && first <= last)
	{
		middle = (first + last) / 2;
		// See if the middle value matches our search value
		if (integers[middle] == value)
		{
			found = true;
			position = middle;
		}
		// See if the middle value is greater than our search value
		else if (integers[middle] > value)
			last = middle - 1;
		else
			first = middle + 1;
	}
	return position;
}
/*********************************************************************
** Description: This is a function that receives the position of the
** found search value and prints out where the element was found. If
** the position is -1, this means the number was not found. 
*********************************************************************/
void searchAlgorithm::binarySearchResults(int position)
{
	if (position == -1)
	{
		cout << " was not found in elements";
	}
	else
	{
		cout << " was found in position ";
		cout << position + 1;
	}
}
