/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This file contains the implentation code of the
** variables and functions needed for creating a new Instructor object
**, setting and returning the name of the person, setting and returning
** the age of the person, setting and returning the rating of the person,
** and lastly setting and returning the number of hours this person
** spends on grading.
*********************************************************************/
#include "Instructor.hpp"
#include <iostream>
using std::string;
using std::cout;
using std::endl;
/*********************************************************************
** Description: This is the default constructor which receives the name
** of the person and their age to instantiate the Instructor object.
*********************************************************************/
Instructor::Instructor(const string& name, int age) : People(name, age)
{
	setRating(rand() % 5);
	setGradingHours(0);
}
/*********************************************************************
** Description: This is the overloaded constructor which receives the name
** , age, gpa, and the amount of hours they spend grading hours to
** instantiate the Instructor object.
*********************************************************************/
Instructor::Instructor(const string& name, int age, double rating, int gradingHours) : People(name, age)
{
	setRating(rating);
	setGradingHours(gradingHours);
}
/*********************************************************************
** Description: This is a function that receives a double (rating) to set
** the rating of the instructor.
*********************************************************************/
void Instructor::setRating(const double rating)
{
	this->rating = rating;
}
/*********************************************************************
** Description: This is a function that returns the rating of the instructor.
*********************************************************************/
double Instructor::getRating() const
{
	return rating;
}
/*********************************************************************
** Description: This is a function that receives an integer to set
** the amount of hours that the instructor spends on grading.
*********************************************************************/
void Instructor::setGradingHours(const int hours)
{
	this->grading_Hours = hours;
}
/*********************************************************************
** Description: This is a function that returns the hours that the instructor
** spends on grading.
*********************************************************************/
int Instructor::getGradingHours() const
{
	return grading_Hours;
}
/*********************************************************************
** Description: This is a function that generates a random number that
** represents how much time the instructor spends grading and then
** sends that number to setGradingHours to set their new hours.
*********************************************************************/
void Instructor::do_work(int x)
{
	int randomHours = (rand() % (40 - 0 + x)) + x;
	this->grading_Hours += randomHours;
	cout << this->getName() << " graded paper for " << this->grading_Hours << " hours." << endl;
}
