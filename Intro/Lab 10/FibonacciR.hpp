/*********************************************************************
** Author: Jonathan Perry
** Date: 6/11/2017
** Description: This file contains the class specification of the
** variables and functions needed for a recursive calculation of
** Fibonacci numbers.
** CITE: https://www.codeproject.com/tips/109443/fibonacci-recursive-and-non-recursive-c
*********************************************************************/
#ifndef FIBONACCIR_HPP
#define FIBONACCIR_HPP
class FibonacciR 
{
private:
	FibonacciR();
	int Fibonacci(const int &n);
	const int *n_;
public:
	FibonacciR(const int &n);
	virtual ~FibonacciR();
	void PrintFibonacci();
};
#endif /* FIBONACCIR_HPP */