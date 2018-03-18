/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This file contains the implentation code of the
** variables and functions needed for creating a new Student object
**, setting and returning the name of the person, setting and returning
** the age of the person, setting and returning the gpa of the person,
** and lastly setting and returning the number of hours this person
** spent on homework.
*********************************************************************/
#include "Student.hpp"
#include <iostream>
using std::string;
using std::cout;
using std::endl;
/*********************************************************************
** Description: This is the default constructor which receives the name
** of the person and their age to instantiate the Student object.
*********************************************************************/
Student::Student(const string& name, int age) : People(name, age)
{
	setGPA(rand() % 4);
	setHW_Hours(0);
}
/*********************************************************************
** Description: This is the overloaded constructor which receives the name
** , age, gpa, and the amount of hours they spend on homework to 
** instantiate the Student object.
*********************************************************************/
Student::Student(const string& name, int age, double gpa, int hwHours) : People(name, age)
{
	setGPA(gpa);
	setHW_Hours(hwHours);
}
/*********************************************************************
** Description: This is a function that receives a double (GPA) to set
** the gpa of the student.
*********************************************************************/
void Student::setGPA(const double gpa)
{
	this->gpa = gpa;
}
/*********************************************************************
** Description: This is a function that returns the GPA of the student.
*********************************************************************/
double Student::getGPA()const
{
	return gpa;
}
/*********************************************************************
** Description: This is a function that receives an integer to set
** the amount of hours that the student spends on homework.
*********************************************************************/
void Student::setHW_Hours(const int hours)
{
	this->hw_Hours = hours;
}
/*********************************************************************
** Description: This is a function that returns the hours that the student
** spends on homework.
*********************************************************************/
int Student::getHW_Hours() const
{
	return hw_Hours;
}
/*********************************************************************
** Description: This is a function that generates a random number that
** represents how much time the student spends doing homework and then
** sends that number to setHW_Hours to set their new hours.
*********************************************************************/
void Student::do_work(int x)
{
	int randomHours = (rand() % (30 - x + 1)) + x; // returns a random # between x and 30
	this->hw_Hours += randomHours;
	cout << this->getName() << " did " << this->hw_Hours << " hours of homework." << endl;
}
