/*********************************************************************
** Author: Jonathan Perry
** Date: 3/1/2017
** Description: This header file defines the class specifications of the
** variables and functions needed for calculating the standard deviation
** of an array of student's test scores.
*********************************************************************/
#ifndef STUDENT
#define STUDENT
#include <string>
using namespace std;

class Student
{
private:
	string name; // Name of the student
	double score; // Score of the student
public:
	// Constructor that takes two values to initialize data members
	Student(string, double);
	// Getters
	string getName() const;
	double getScore() const;
};
#endif // !
