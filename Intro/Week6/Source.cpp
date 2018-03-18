#include "Point.hpp"
#include "LineSegment.hpp"
#include <iostream>
using namespace std;

int main()
{
	Point p1(4.3, 7.52);
	Point p2(-17.0, 1.5);
	double dist = p1.distanceTo(p2);
	LineSegment ls1(p1, p2);
	double length = ls1.length();
	double slope = ls1.slope();
	cout << "distance" << dist << endl;
	cout << "length: " << length << endl;
	cout << "slope: " << slope << endl;
}