/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This header file defines the class specifications of
** variables and functions needed for creating a new Student object
**, setting and returning the name of the person, setting and returning
** the age of the person, setting and returning the gpa of the person,
** and lastly setting and returning the number of hours this person
** spent on homework.
*********************************************************************/
#ifndef STUDENT_HPP
#define STUDENT_HPP
#include "People.hpp"
class Student : public People
{
private:
	int hw_Hours;
	double gpa;
public:
	Student(const std::string&, int);
	Student(const std::string&, int, double, int);

	void setGPA(const double);
	double getGPA() const;
	
	void setHW_Hours(const int);
	int getHW_Hours() const;

	virtual void do_work(int);
	//Student* getPerson(std::string);
};
#endif // !STUDENT_HPP
#pragma once
