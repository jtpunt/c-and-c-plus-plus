/*********************************************************************
** Author: Jonathan Perry
** Date: 2/8/2017
** Description: This header file defines the class specifications of the
** variables and functions needed for calculating the volume and surface
** area of a box.
*********************************************************************/
#ifndef BOX_HPP
#define BOX_HPP
class Box
{
private:
	// Variables used for the dimensions the box
	double height, width, length;
public:
	// Default constructor prototype
	Box();
	// Constructor prototype that takes 3 doubles and passes them to the set methods below
	Box(double, double, double);

	// setter prototypes, each function checks that the input is >= 0
	bool setHeight(double); // Receives double to set as height
	bool setWidth(double); // Receives double to set as width
	bool setLength(double); // Receives double to set as length
	// getter prototypes
	double getVolume(); // Calculates the volume of the box
	double getSurfaceArea(); // Calculates the surface area of the box
};
#endif
