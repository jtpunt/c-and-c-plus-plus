/*********************************************************************
** Author: Jonathan Perry
** Date: 2/8/2017
** Description: This file contains the implentation code of the
** variables and functions needed for calculating the volume and surface
** area of a box.
*********************************************************************/
#include "Box.hpp"
using namespace std;
/*********************************************************************
** Description: This is the default constructor of the Box class which
** sets height, width, and length all to 1.
*********************************************************************/
Box::Box()
{
	setHeight(1);
	setWidth(1);
	setLength(1);
}
/*********************************************************************
** Description: This is a constructor of the Box class which
** takes 3 doubles and passes them to the set methods below.
*********************************************************************/
Box::Box(double h, double w, double l)
{
	setHeight(h);
	setWidth(w);
	setLength(l);
}
/*********************************************************************
** Description: This is an mutator function that receives a value
** and then sets that value to the class variable height.
*********************************************************************/
bool Box::setHeight(double h)
{
	bool validData = true; 
	if (h >= 0) // If the height(h) is valid
		height = h; // copy it to height
	else
		validData = false; // else leave height unchanged
	return validData;
}	
/*********************************************************************
** Description: This is an mutator function that receives a value
** and then sets that value to the class variable width.
*********************************************************************/
bool Box::setWidth(double w)
{
	bool validData = true;
	if (w >= 0) // If the width(w) is valid
		width = w; // copy it to width
	else
		validData = false; // else leave width unchanged
	return validData;
}
/*********************************************************************
** Description: This is an mutator function that receives a value
** and then sets that value to the class variable length.
*********************************************************************/
bool Box::setLength(double l)
{
	bool validData = true;
	if (l >= 0) // If the length(l) is valid
		length = l; // copy it to length
	else
		validData = false; // else leave length unchanged
	return validData;
}
/*********************************************************************
** Description: This is an accessor function that returns
** the calculation for volume.
*********************************************************************/
double Box::getVolume()
{
	return height * width * length;
}
/*********************************************************************
** Description: This is an accessor function that returns
** the calculation for total surface area (2lw + 2lh + 2wh).
*********************************************************************/
double Box::getSurfaceArea()
{
	return (2*(length * width) + 2*(length * height) + 2*(width * height)); 
}
