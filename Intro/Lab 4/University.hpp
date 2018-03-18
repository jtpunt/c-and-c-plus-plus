/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This header file defines the class specifications of
** variables and functions needed for creating a new University object
**, setting and returning the name of the University, and printing
** information about each building and person of the University.
*********************************************************************/
#ifndef UNIVERSITY_HPP
#define UNIVERSITY_HPP
#include <string>
#include <memory>
#include <vector>
class University
{
protected:
	std::string name;
public:
	University();
	University(const std::string&);

	void setName(const std::string&);
	std::string getName() const;

	void print_Building_Info(const std::string, const double, const std::string);
	void print_People_Info(const  std::string name, const int age, double gpa_or_rating, const int hours);

};
#endif // !UNIVERSITY_HPP

