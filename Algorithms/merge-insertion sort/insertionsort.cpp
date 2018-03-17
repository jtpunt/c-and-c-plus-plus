/*********************************************************************
** Author: Jonathan Perry
** Date: 1/13/2018
** Description: This file contains the implementation code of the
** insertion sort algorithm.
*********************************************************************/
#include "insertionsort.hpp"
#include <vector>
using std::vector;
// This function receives the address to a vector so that the function
// can manipulate/sort the vector using the insertion sort algorithm.
void insertionSort(vector <int> &v){
	int key, j;
	for(int i  = 1; i < v.size(); i++){
		key = v[i];
		j = i - 1;
		while(j >= 0 && v[j] > key){
			v[j+1] = v[j--];
		}
		v[j+1] = key;
	}
}

