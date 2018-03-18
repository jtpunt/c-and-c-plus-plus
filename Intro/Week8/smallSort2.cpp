/*********************************************************************
** Author: Jonathan Perry
** Date: 2/1/2017
** Description: This fuction takes the addresses of 3 integers and sorts 
** their values into ascending order before printing them out.
*********************************************************************/
#include <iostream>
using namespace std;
void smallSort2(int *a, int *b, int *c)
{
	int temp;
	do
	{
		// Switch a and b if out of order
		if (*a > *b) 
		{
			temp = *b; // Assign temp to equal b
			*b = *a; // Reassign b to equal a  
			*a = temp; // Reassign a to what was originally b
		}
		// Switch b and c if out of order
		else if (*b > *c)
		{
			temp = *c; // Assign temp to equal c now
			*c = *b;// Reassign c to equal b
			*b = temp; // Reassign b to equal what was originally c
		}
	} 
	// Keep looping until the numbers are in ascending order
	while ((*a > *b) | (*b > *c) | (*a > *c));
}