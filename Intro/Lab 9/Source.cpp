#include <iostream>
#include <stdlib.h>
#include "FibonacciR.hpp"
#include "FibonacciNR.hpp"
using namespace std;
void Usage() 
{
	cout << "Correct Usage:" << endl;
	cout << "./Fibonacci [n]" << endl;
}
int main(int argc, char** args) {
	try {
		const char* input; //Note: char by default initializes to '\0'

		if (args[1] != 0)
		{
			cout << "1st passed arguement: '" << args[1] << "'" << endl;
			input = args[1];
		}
		int n = atoi(input);
		cout << "Finding '" << n << "'th " << "fibonacci number...." << endl;
		cout << "Calling Recursive Fibonacci implementation" << endl;
		FibonacciR fr(n);
		fr.PrintFibonacci();
		cout << "Calling Non-Recursive Fibonacci implementation" << endl;
		FibonacciNR fnr(n);
		fnr.PrintFibonacci();
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