/*********************************************************************
** Author: Jonathan Perry
** Date: 2/8/2017
** Description: This file contains the implentation code of the
** variables and functions needed for calculating the standard 
** deviation of an array of student test scores.
*********************************************************************/
#include "Student.hpp"
#include <string>
using namespace std;
/*********************************************************************
** Description: This is a constructor of the Student class which
** takes 2 variables and uses them to initialize the data members.
*********************************************************************/
Student::Student(string studentName, double studentScore)
{
	name = studentName;
	score = studentScore;
}
// Getters
string Student::getName() const
{
	return name;
}
double Student::getScore() const
{
	return score;
}