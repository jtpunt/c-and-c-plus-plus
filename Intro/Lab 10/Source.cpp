/*********************************************************************
** Author: Jonathan Perry
** Date: 6/11/2017
** Description: This file contains the implementation code of the
** variables and functions needed for a recursive and non-recursive
** calculation of Fibonacci numbers so that differences between running
** time can be observed.
** CITE: https://www.codeproject.com/tips/109443/fibonacci-recursive-and-non-recursive-c
*********************************************************************/
#include <iostream>
#include <stdio.h>      /* printf */
#include <stdlib.h>
#include <ctime> // clock_t, clock, CLOCKS_PER_SEC
#include "FibonacciR.hpp"
#include "FibonacciNR.hpp"
using namespace std;
void Usage()
{
	cout << "Correct Usage:" << endl;
	cout << "./Fibonnaci [n]" << endl;
}
int main(int argc, char** args)
{
	clock_t recursive;
	clock_t nonRecursive;
	int fibNumberR;
	int fibNumberNR;

	cout << "Enter in the sequence number in the Fibonacci that you want to calculate." << endl;
	cout << "(for the recusive fibonacci implementation): ";
	cin >> fibNumberR;

	cout << "Enter in the sequence number in the Fibonacci that you want to calculate." << endl;
	cout << "(for the non-recursive fibonacci implementation): ";
	cin >> fibNumberNR;
	try {

		cout << "Finding '" << fibNumberR << "'th " << "fibonacci number...." << endl;
		cout << "Calling Recursive Fibonacci implementation" << endl;
		recursive = clock();
		FibonacciR fr(fibNumberR);
		fr.PrintFibonacci();
		recursive = clock() - recursive;
		printf("It took me %d clicks (%f seconds).\n", recursive, ((float)recursive) / CLOCKS_PER_SEC);
		cout << endl;

		cout << "Calling Non-Recursive Fibonacci implementation" << endl;
		nonRecursive = clock();
		FibonacciNR fnr(fibNumberNR);
		fnr.PrintFibonacci();
		nonRecursive = clock() - nonRecursive;
		printf("It took me %d clicks (%f seconds).\n", nonRecursive, ((float)nonRecursive) / CLOCKS_PER_SEC);
		cout << "Done!!!!" << endl;
		return 0;
	}
	catch (...)
	{
		cout << "Oops an error occured! Please check usage" << endl;
		Usage();
		return 1;
	}
}
