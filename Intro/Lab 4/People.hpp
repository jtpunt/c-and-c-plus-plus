/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This header file defines the class specifications of
** variables and functions needed for creating a new People object
**, setting and returning the name of the person, and setting and returning
** the age of the person.
*********************************************************************/
#ifndef PEOPLE_HPP
#define PEOPLE_HPP
#include "University.hpp"
class People : public University
{
protected:
	int age;
public:
	People(const std::string&, int);

	void setAge(int);
	int getAge();

	virtual void do_work(int) = 0;
};
#endif // !PEOPLE_HPP
