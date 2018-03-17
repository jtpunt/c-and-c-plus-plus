/*
 * cut-rod.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: jonathan
 */
#include "cut-rod.hpp"
#include <math.h>
#include <iostream>
#include <iomanip>
using std::vector;
using std::cout;
using std::setw;

int max(int a, int b) { return (a > b)? a: b;}

/*********************************************************************************
 * As rod_length grows in our outer loop, we find the best prices for each
 * different positions of the cuts we can make in the inner loop and compare
 * their values to find the maximum value obtainable for that given rod_length. Once
 * the outer loop completes, we have found the maximum value obtainable for a rod of
 * length n.
 *
 * We first get the price of our first cut at index cut_pos from our price table.
 * We then add this value to the value obtained from a second cut.
 * For there to be a second cut, we look at 1 of two conditions below.
 * 	- When rod_length - cut_pos - 1 = 0, we cannot cut the rod up anymore.
 * 	- When rod_length - cut_pos - 1 > 0, we have some of the rod leftover from the
 * 	  previous cut and can make a cut at another position.
 * However, rod_length - cut_pos - 1 < rod_length, meaning, we have already calculated
 * the maximum price obtainable from making a cut at rod_length - cut_pos - 1 in a
 * previous iteration of the outer loop, so we use this price from the max_revenue vector
 * and add it to the value obtained from the fist cut we made.
 *
 * After the outer loop completes an iteration, the maximum value obtainable for that
 * given rod length is stored at the index rod_length in the max_revenue vector.
 *************************************************************************************/
int bottomUpCutRod(vector<int> price, int n){
	vector<int> max_revenue(n+1);
	max_revenue[0] = 0; // we cannot make any money off of 0 cuts
	for(int rod_length = 1; rod_length <= n; rod_length++){
		int revenue = -1;
		for(int cut_pos = 0; cut_pos < rod_length; cut_pos++){
			int length_leftover = rod_length - cut_pos - 1;
			revenue = max(revenue, price[cut_pos] + max_revenue[length_leftover]);
			cout << setw(2) << revenue << " ";
		}
		cout << "\n";
		max_revenue[rod_length] = revenue; // stores the optimal price for the current rod_length
	}
	return max_revenue[n];
}
int main(){
	vector <int> price{1, 5, 8, 9, 10, 17, 17, 20};
	cout << "\nMax revenue obtainable for a rod of size " << price.size() << ": "<< bottomUpCutRod(price, price.size());
}

