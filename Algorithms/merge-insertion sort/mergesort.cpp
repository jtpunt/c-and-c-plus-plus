/*********************************************************************
** Author: Jonathan Perry
** Date: 1/13/2018
** Description: This file contains the implementation code of the
** merge sort algorithm.
*********************************************************************/
#include "mergesort.hpp"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

// This function receives the address to a vector so that the function
// can manipulate/merge the two halves in sorted order.
void merge(vector <int> &v, int low, int high, int mid){
	int i = low, j = mid + 1;
	vector <int> temp;

	// Merge the two halves into temp
	while (i <= mid && j <= high){
		if (v[i] < v[j])
			temp.push_back(v[i++]);
		else
			temp.push_back(v[j++]);
	}
	// Push all the remaining values from i to mid into temp
	while (i <= mid)
		temp.push_back(v[i++]);
	// Push all the remaining values from j to high into temp
	while (j <= high)
		temp.push_back(v[j++]);
	// Assign the sorted data stored from temp to v.
	for (i = low; i <= high; i++)
		v[i] = temp[i-low];
}
// This function receives the address to a vector so that the function
// can recursively split the vector in two halves until both halves
// contain 1 element.
void mergeSort(vector <int> &v, int low, int high){
	int mid;
	if (low < high){
		mid= (low + high)/2;
		mergeSort(v, low, mid); // sort the 1st half
		mergeSort(v, mid+1, high); // sort the 2nd half

		merge(v, low, high, mid);
	}
}


