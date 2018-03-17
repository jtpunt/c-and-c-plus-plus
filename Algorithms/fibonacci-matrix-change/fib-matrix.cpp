/*
 * fib-matrix.cpp
 *
 *  Created on: Jan 31, 2018
 *      Author: jonathan
 */
#include <iostream>
using std::cout;
// This function does 1 less calculation than the version using a 2d matrix
// and uses a 1d array of 3 total elements, versus a 2d array of 4 total elements,
// which helps save a bit of space
void multiply(int F[3], int M[3]){
	cout << F[0] << " " << F[1] << " " << F[2] << "\n";
	cout << M[0] << " " << M[1] << " " << M[2] << "\n";
	int x = F[0]*M[0]+F[1]*M[1]; // Fn+1*Mn+1 + Fn*Mn
	int y = F[0]*M[1]+F[1]*M[2]; // Fn+1*Mn + Fn*Mn-1
	int z = F[1]*M[1]+F[2]*M[2]; // Fn*Mn + Fn-1*Mn-1
	F[0] = x; // Fn+1
	F[1] = y; // Fn
	F[2] = z; // Fn-1
	cout << x << " " << y << " " << z << "\n\n";
}
// Returns the nth Fibonacci number
void power(int F[3], int n){
	if( n == 0 || n == 1)
		return;
	int M[3] = {1, 1, 0};
	power(F, n/2);
    multiply(F, F);

    if (n%2 != 0){ // n is not even
    	cout << "N is not even at " << n << "\n";
    	multiply(F, M);
    }
}
/* function that returns nth Fibonacci number */

int fib(int n){
  int F[3] = {1, 1, 0}; // Fn+1, Fn, Fn-1
  if (n == 0)
      return 0;
  power(F, n-1);

  return F[0];
}
/* Driver program to test above function */
int main(){
	int n = 2;
	cout << fib(9);
	return 0;
}




