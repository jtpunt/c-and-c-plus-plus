/*********************************************************************
** Author: Jonathan Perry
** Date: 4/23/2017
** Description: This header file defines the class specifications of
** variables and functions needed for creating a new Instructor object
**, setting and returning the name of the person, setting and returning
** the age of the person, setting and returning the rating of the person,
** and lastly setting and returning the number of hours this person
** spends on grading.
*********************************************************************/
#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP
#include "People.hpp"
class Instructor : public People
{
private:
	int grading_Hours;
	double rating;
public:
	Instructor(const std::string&, int);
	Instructor(const std::string&, int, double, int);
	void setRating(const double);
	double getRating() const;

	void setGradingHours(const int);
	int getGradingHours() const;

	virtual void do_work(int);
};
#endif // !INSTRUCTOR_HPP
#pragma once
#pragma once
