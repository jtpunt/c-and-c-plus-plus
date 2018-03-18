/*********************************************************************
** Author: Jonathan Perry
** Date: 4/23/2017
** Description: This header file defines the class specifications of
** variables and functions needed for creating a new Building object
**, setting and returning the size of the Building, and setting and returning
** the address of the building.
*********************************************************************/
#ifndef BUILDINGS_HPP
#define BUILDINGS_HPP
#include "University.hpp"
#include <string>
class Buildings : public University
{
private:
	int size; // Stores the total sqft of the building
	std::string address;
public:
	Buildings(const std::string&, int, const std::string& );
	void setSize(const int);
	int getSize() const;

	void setAddress(const std::string&);
	std::string getAddress() const;
};
#endif // !BUILDINGS_HPP

