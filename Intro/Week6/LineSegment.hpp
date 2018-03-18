/*********************************************************************
** Author: Jonathan Perry
** Date: 2/15/2017
** Description: This header file defines the class specifications of the
** variables and functions needed for calculating the length and slope
** between two endpoint objects from the Point class.
*********************************************************************/
#ifndef LINESEGMENT
#define LINESEGMENT
#include "Point.hpp"
class LineSegment
{
private:
	Point end1, end2;
public:
	LineSegment(const Point &, const Point &);
	// getters
	Point getEnd1();
	Point getEnd2();
	// setters
	void setEnd1(const Point &);
	void setEnd2(const Point &);
	// both functions below call functions within the Point class
	double length(); // returns the distance between two endpoints
	double slope(); // returns the slope between two endpoints
};
#endif