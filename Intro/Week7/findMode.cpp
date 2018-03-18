/*********************************************************************
** Author: Jonathan Perry
** Date: 2/22/2017
** Description: This file contains the function for finding the mode 
** of a set of data in an array that the function receives and returns the 
** value(s) that have the highest frequency in ascending order.
*********************************************************************/
#include <algorithm>
#include <vector>
using std::vector;
using std::sort;
/*********************************************************************
** Description: This is a function that receives both a set of data from an 
** array and also receives the size of the array to determine the mode
** of that set of data. The function stores the value(s) of the set
** that occur the most into a vector and then returns that vector.
*********************************************************************/
vector <int> findMode(int nums[], int arraySize)
{
	int maximumFrequency = 0; // Stores how often each number appears in a set of data
	vector <int> mode; // Vector to store the mode(s) of the set of data

	sort(nums, nums + arraySize); // Sort array into ascending order

	for (int index = 0; index < arraySize; index++) // Loop through the array
	{
		int currentFrequency = 1; // Each number appears once in the set of numbers

		// Compare value at the array's current subscript to the next element
		while (nums[index] == nums[index + 1])
		{
			currentFrequency++; // Increments by 1 each time the number appears again

			/* The index increments each time the while loop's condition evaluates to true.
			   When the while loop's condition evaluates to false, the for loop's next iteration 
			   picks up at the next [index] where the while loop's [index] left off.
			   This prevents redundancy from the for loop checking the same numbers again.*/
			index++; 
		}
		// Check to see if different numbers of the set appear the same number of times
		if (currentFrequency == maximumFrequency) 
		{
			// Store the numbers that have the same frequency in the set of numbers
			mode.push_back(nums[index]); 
		}
		// Check to see if a number in the set occurs more than the current maximum frequency
		if (currentFrequency > maximumFrequency)
		{
			maximumFrequency = currentFrequency; // Readjust the new maximum frequency
			mode.clear(); // Clear the vector of all data
			mode.push_back(nums[index]); // Store the single number
		}
	}
	return mode; // Send the vector containing the mode(s)
	
}
