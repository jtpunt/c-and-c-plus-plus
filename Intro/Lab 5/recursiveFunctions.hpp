/*********************************************************************
** Author: Jonathan Perry
** Date: 5/07/2017
** Description: This header file defines the class specifications of the
** variables and functions needed for recursively displaying the reverse
** of a user-entered string, recursively calculating the sum of N
** integers, and for recursively calculating the triangular number for 
** N (which is the sum of all items that form a triangle with N rows).
*********************************************************************/
#ifndef RECURSIVEFUNCTIONS_HPP
#define RECURSIVEFUNCTIONS_HPP
#include <memory>
#include <string>
class recursiveFunctions
{
private:
	int sum;
	int times;
	int triangularN_sum;
public:
	recursiveFunctions();
	void reverseString(std::string);
	void createArray(int);
	void getArrayInput(std::unique_ptr<int[]> &, int);
	void triangularN(int);
};
#endif // !RECURSIVEFUNCTIONSWW_HPP
