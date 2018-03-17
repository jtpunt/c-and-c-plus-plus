/*
 * fibonacci.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: jonathan
 */
#include <iostream>
using std::cout;
using std::endl;

long int fibonacci(int n){
	int n1, n2;
	// base case: n = 0
	if(n == 0){
		cout << "BASE CASE N = 0" << endl;
		return 0;
	}
	// base case: n = 1
	else if(n == 1){
		cout << "BASE CASE N = 1" << endl;
		return 1;
	}
	else{
		n1 = fibonacci(n-1);
		n2 = fibonacci(n-2);
		cout << "n = " << n << endl;
		cout << "n1 = " << n1 << endl;
		cout << "n2 = " << n2 << endl;
		return n1 + n2;
	}
}
int main(){
	cout << "fibonacci when n = 10: " << fibonacci(10) << endl;
	return 0;
}


