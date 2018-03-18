/*********************************************************************
** Author: Jonathan Perry
** Date: 2/15/2017
** Description: This file contains the implentation code of the
** variables and functions needed for calculating the distance from two
** separate points.
*********************************************************************/
#include "Point.hpp"
#include <cmath>
/*********************************************************************
** Description: This is the default constructor of the Point class which
** uses the set methods below to initialize both coordinates to 0.
*********************************************************************/
Point::Point()
{
	setXCoord(0);
	setYCoord(0);
}
/*********************************************************************
** Description: This is a constructor of the Point class which
** takes 2 doubles and passes them to the set methods below to initialize
** the (x,y) coordinates.
*********************************************************************/
Point::Point(double x, double y) 
{
	setXCoord(x);
	setYCoord(y);
}
// getters
double Point::getXCoord()
{
	return x_coordinate;
}
double Point::getYCoord()
{
	return y_coordinate;
}
// setters
void Point::setXCoord(double x)
{
	x_coordinate = x;
}
void Point::setYCoord(double y)
{
	y_coordinate = y;
}
/*********************************************************************
** Description: This is an accessor function that takes a constant 
** reference to another Point as a parameter and then returns the 
** distance from the Point that was passed as a parameter to the Point
** that we called the method with.
*********************************************************************/
double Point::distanceTo(const Point &reference)
{
	double xDistance = reference.x_coordinate - x_coordinate,
		   yDistance = reference.y_coordinate - y_coordinate;
	return sqrt(xDistance*xDistance + yDistance*yDistance);
}