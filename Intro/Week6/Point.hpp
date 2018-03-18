/*********************************************************************
** Author: Jonathan Perry
** Date: 2/15/2017
** Description: This header file defines the class specifications of the
** variables and functions needed for calculating the distance from two
** separate points.
*********************************************************************/
#ifndef POINT_HPP
#define POINT_HPP
class Point
{
private:
	double x_coordinate, y_coordinate;
public:
	// constructors
	Point();
	Point(double, double); 
	// getters
	double getXCoord(); 
	double getYCoord();

	// setters
	void setXCoord(double);
	void setYCoord(double);

	double distanceTo(const Point&); // Receives a reference to a Point object
};
#endif
