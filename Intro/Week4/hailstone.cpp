/*********************************************************************
** Author: Jonathan Perry
** Date: 2/1/2017
** Description: This fuction takes a number and returns how many steps
** it takes to reach 1 based on following two rules to find the next
** number in the sequence:
**		If the number is even, divide it by 2 to get the next sequence.
**		If the number is odd, multiply it by 3 and add 1 to get the 
**		next sequence.
*********************************************************************/
int hailstone(int startNumber)
{
	int counter = 0;
	// Check to see if the number is 1
	while (startNumber != 1)
	{
		// Check to see if the number is even
		if (startNumber % 2 == 0)
		{
			startNumber /= 2;
		}
		else // The number is odd
		{
			// Multiply it by 3 and increment 1
			(startNumber *= 3)++;
		}
		counter++; //increment each step
	}
	return counter;
}