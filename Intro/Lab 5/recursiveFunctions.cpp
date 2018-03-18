/*********************************************************************
** Author: Jonathan Perry
** Date: 5/07/2017
** Description: This file contains the implementation code of the
** variables and functions needed for recursively displaying the reverse
** of a user-entered string, for recursively calculating the sum of N
** integers, and for recursively calculating the triangular number for
** N (which is the sum of all items that form a triangle with N rows).
*********************************************************************/
#include "recursiveFunctions.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::unique_ptr;
recursiveFunctions::recursiveFunctions()
{
	sum = 0;
	times = 0;
	triangularN_sum = 0;
}
/*********************************************************************
** Description: This is a function that prints out the reverse of a 
** user-specified string. The function achieves this by
** displaying the last character of the string it received and then recursively
** calling this function (with the last character truncated from the string), 
** until the length of the string is zero.
*********************************************************************/
void recursiveFunctions::reverseString(string myString)
{
	if (myString.length() == 0)
	{
		cout << "(newline)." << endl;
	}
	else
	{
		cout << myString[myString.length() - 1];
		reverseString(myString.substr(0, myString.length() - 1));
	}
}
/*********************************************************************
** Description: This is a function that uses a unique pointer to point 
** to a dynamically allocated array of integers, where the amount of integers
** allocated is specified by the user.
*********************************************************************/
void recursiveFunctions::createArray(int size)
{
	unique_ptr<int[]> arrayPtr(new int[size]);
	getArrayInput(arrayPtr, size);
}
/*********************************************************************
** Description: This is a function that stores integers entered by the
** user into an array by recursively calling this function after each
** individual integer is gathered until the function arrives at the end 
** of the array.
*********************************************************************/
void recursiveFunctions::getArrayInput(unique_ptr<int[]>& arrayPtr, int size)
{
	if (size > 0)
	{
		cout << "(Enter in your next number:)";
		cin >> arrayPtr[--size]; 
		sum += arrayPtr[size];
		getArrayInput(arrayPtr, size);
	}
	else
	{
		cout << "The sum of the numbers is " << sum << "." << endl;
		sum = 0;
	}
}
/*********************************************************************
** Description: This is a function that receives an integer N (where N is 
** the triangular number to be solved for). Each time n > 0, 
** the value of n is added to the variable triangularN_sum, and n is 
** decremented by 1 and that value of N is used to recursively call 
** triangularN until n is zero.
*********************************************************************/
void recursiveFunctions::triangularN(int n)
{
	if (n > 0)
	{
		triangularN_sum += n--;
		triangularN(n);
	}
	else
	{
		cout << "The triangular number is: " << triangularN_sum << endl;
		// Reset all values so user can calculate another triangular number
		triangularN_sum = 0;
	}
}