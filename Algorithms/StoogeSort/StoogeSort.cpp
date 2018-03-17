/*********************************************************************
** Author: Jonathan Perry
** Date: 1/21/2018
** Description: This file contains the implementation code of the
** StoogeSort algorithm.
*********************************************************************/
#include "StoogeSort.hpp"
#include <math.h>
using std::vector;
void StoogeSort(vector<int> &A, int low, int high){
	int n = high-low+1;
	if(n == 2 && A[low] > A[high]){
		int temp = A[low];
		A[low] = A[high];
		A[high] = temp;
	}
	else if(n > 2){
		int m = ceil(2.0*n/3);
		StoogeSort(A, low, low+(m - 1)); // Sorts the first 2/3 elements
		StoogeSort(A, low+(n-m), high); // Sorts the last 2/3 elements
		StoogeSort(A, low, low+(m - 1)); // Sorts the first 2/3 elements
	}
}

