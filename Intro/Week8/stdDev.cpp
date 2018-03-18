/*********************************************************************
** Author: Jonathan Perry
** Date: 2/8/2017
** Description: This file contains the function for calculating the
** standard deviation of student test scores.
*********************************************************************/
#include <cmath>
#include "Student.hpp"
using namespace std;
/*********************************************************************
** Description: This is a function that receives an array of pointers
** to Student objects and the size of the array and then returns the 
** standard deviation for the student scores. (Using the population 
** standard deviation formula.)
*********************************************************************/
double stdDev(const Student *arrayPtr, int size)
{
	double sum, mean, standardDeviation;
	sum = mean = standardDeviation = 0.0;
	// Loops through each student object in the array
	for (int i = 0; i < size; i++, arrayPtr++)
	{
		// Sum the scores of each student object by calling the getScore member function
		sum += arrayPtr->getScore();
	}
	mean = sum / size;

	arrayPtr--; // Decrement the array so it's no longer out of bounds

	// Loops in reverse through each student object in the array
	for (int i = 0; i < size; i++, arrayPtr--)
	{
		// Sum the deviations from the square of the current score minus the average score
		standardDeviation += pow(arrayPtr->getScore() - mean, 2);
	}
	return sqrt(standardDeviation / size);
}