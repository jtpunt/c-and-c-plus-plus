/*********************************************************************
** Author: Jonathan Perry
** Date: 2/1/2017
** Description: This fuction shows us the distance in meters in which
** an object has fallen over time.
*********************************************************************/
double fallDistance(double fallTime)
{
	// const - gravity is a variable that never changes
	const double GRAVITY = 9.8; 
	// Calculates the distance covered over time and then returns that value
	return GRAVITY * (fallTime * fallTime) / 2; 
}