/*********************************************************************
** Author: Jonathan Perry
** Date: 2/15/2017
** Description: This file contains the implentation code of the
** variables and functions needed for length and slope specified by
** two endpoint objects from the Point class.
*********************************************************************/
#include "LineSegment.hpp"
/*********************************************************************
** Description: This is a constructor of the LineSegment class which
** takes 2 Point objects and passes them to the set methods below.
*********************************************************************/
LineSegment::LineSegment(const Point &end_1, const Point &end_2)
{
	setEnd1(end_1);
	setEnd2(end_2);
}
// getters
Point LineSegment::getEnd1()
{
	return end1;
}
Point LineSegment::getEnd2()
{
	return end2;
}
// setters
void LineSegment::setEnd1(const Point &end_1)
{
	end1 = end_1;
}
void LineSegment::setEnd2(const Point &end_2)
{
	end2 = end_2;
}
/*********************************************************************
** Description: This is an accessor function that calls
** the function within the Point class to calculate the distance between
** two endpoints and then returns that value.
*********************************************************************/
double LineSegment::length()
{
	return end1.distanceTo(end2);
}
/*********************************************************************
** Description: This is an accessor function that calls
** the function within the Point class to receive (x,y) coordinates 
** to calculate the slope between two endpoints and then returns that value. 
** If the line segment is a vertical slope, the functions returns "inf", 
** or infinity.
*********************************************************************/
double LineSegment::slope()
{
	return (end2.getYCoord() - end1.getYCoord()) / (end2.getXCoord() - end1.getXCoord());
}