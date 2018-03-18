/*********************************************************************
** Author: Jonathan Perry
** Date: 6/11/2017
** Description: This file contains the class specification of the
** variables and functions needed for a non-recursive calculation of
** Fibonacci numbers.
** CITE: https://www.codeproject.com/tips/109443/fibonacci-recursive-and-non-recursive-c
*********************************************************************/
#ifndef FIBONACCINR_HPP
#define FIBONACCINR_HPP
class FibonacciNR 
{
private:
	FibonacciNR();
	int Fibonacci(const int &n);
	const int* n_;
public:
	FibonacciNR(const int &n);
	virtual ~FibonacciNR();
	void PrintFibonacci();
};
#endif /* FIBONACCINR_HPP */