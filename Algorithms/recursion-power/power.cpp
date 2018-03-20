/*
 * power.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: jonathan
 */
#include <iostream>
using std::cout;
using std::endl;

long int power(long int x, long int n){
	long int temp;
	// base case: a^0 = 0
	if(x == 0){
		cout << "BASE CASE: Returning x = " << x << endl;
		return 1;
	}
	// base case: a^1 = 1
	else if(n == 1){
		cout << "BASE CASE: Returning n = " << n << endl;
		return x;
	}
	// case: even?
	else if((n % 2) == 0){
		temp = power(x, n/2);
		cout << "\ntemp = " << temp << endl;
		cout << "n = " << n << endl;
		cout << "x = " << x << endl;
		cout << "EVEN: Returning (temp*temp)" << temp << " * " << temp << " = "<< temp*temp << endl;
		return temp*temp;
	}
	// case: odd?
	else{
		temp = power(x, (n-1)/2);
		cout << "\ntemp = " << temp << endl;
		cout << "n = " << n << endl;
		cout << "x = " << x << endl;
		cout << "ODD: Returning x*(temp*temp)" << x << " * " << temp << " * " << temp << " = "<< temp*temp << endl;
		return x * temp * temp;
	}
}
int main(){
	cout << "15^13 = " << power(15,13) << endl;
	return 0;
}


