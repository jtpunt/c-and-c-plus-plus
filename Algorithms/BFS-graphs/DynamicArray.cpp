/*
 * DynamicArray.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: Jonathan Perry
 */
#include "DynamicArray.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>
using std::cout;

int compare(int left, int right){
	if(left < right)
		return -1;
	else if(left > right)
		return 1;
	else
		return 0;
}
struct DynamicArray{
	TYPE* data;
	int size;
	int capacity;
};

// --- Dynamic array ---

static void setCapacity(DynamicArray* array, int capacity){
	TYPE* data = new TYPE[capacity];
	for (int i = 0; i < dySize(array); i++){
		data[i] = dyGet(array, i);
	}
	delete [] array->data;
	array->data = data;
	array->capacity = capacity;
}

static void init(DynamicArray* array, int capacity){
	assert(capacity > 0);
	array->data = NULL;
	array->size = 0;
	setCapacity(array, capacity);
}

DynamicArray* dyNew(int capacity){
	DynamicArray* array = new DynamicArray;
	init(array, capacity);
	return array;
}

void dyDelete(DynamicArray* array){
	for(int i = 0; i < dySize(array); i++){
		delete dyGet(array, i);
	}
	delete [] array->data;
	delete array;
}

void dyAdd(DynamicArray* array, TYPE value){
	if (array->size >= array->capacity){
		setCapacity(array, 2 * array->capacity);
	}
	dyPut(array, value, dySize(array));
	array->size++;
}

void dyAddAt(DynamicArray* array, TYPE value, int position){
	assert(position <= array->size);
	dyAdd(array, value);
	for (int i = dySize(array) - 1; i > position; i--){
		dySwap(array, i, i - 1);
	}
}

void dyPut(DynamicArray* array, TYPE value, int position){
	assert(position <= array->size);
	array->data[position] = value;
}

void dyRemoveAt(DynamicArray* array, int position){
	assert(position < dySize(array));
	for (int i = position; i < dySize(array) - 1; i++){
		dyPut(array, dyGet(array, position + 1), position); // slide values to the left
	}
	array->size--;
}

TYPE dyGet(DynamicArray* array, int position){
	assert(position <= dySize(array));
	return array->data[position];
}

int dySize(DynamicArray* array){
	return array->size;
}
int dyCap(DynamicArray* array){
	return array->capacity;
}

void dySwap(DynamicArray* array, int position1, int position2){
	assert(position1 <= dySize(array));
	assert(position2 <= dySize(array));
	TYPE temp = array->data[position1];
	dyPut(array, dyGet(array, position2), position1);
	dyPut(array, temp, position2);
}



int binarySearch(DynamicArray* array, int value){
	int low = 0;
	int high = array->size - 1;
	while (low <= high){
		int middle = (low + high) / 2;
		if (compare(value, 	dyGet(array, middle)->i) < 0){
			high = middle - 1;
		}
		else if (compare(value, dyGet(array, middle)->i) > 0){
			low = middle + 1;
		}
		else{
			return middle;
		}
	}
	return low;
}

// --- Heap ---

/**
* Adjusts heap to maintain the heap property.
* @param heap
* @param last  index to adjust up to.
* @param position  index where adjustment starts.
* @param compare  pointer to compare function.
*/
void adjustHeap(DynamicArray* heap, int last, int position){
	int small, left = (2 * position) + 1;
	int right = (2 * position) + 2;
	if (right < last){
		if (compare(dyGet(heap, left)->d, dyGet(heap, right)->d) == -1)
			small = left;
		else
			small = right;
		if (compare(dyGet(heap, small)->d, dyGet(heap, position)->d) == -1){
			dySwap(heap, position, small);
			adjustHeap(heap, last, small);
		}
	}
	else if (left < last){
		if (compare(dyGet(heap, left)->d, dyGet(heap, position)->d) == -1){
			dySwap(heap, position, left);
			adjustHeap(heap, last, left);
		}
	}
}

/**
* Builds a valid heap from an arbitrary array.
* @param heap  array with elements in any order.
* @param compare  pointer to compare function.
*/
void buildHeap(DynamicArray* heap){
	assert(heap != 0);
	int size = dySize(heap);
	for (int i = size / 2 - 1; i >= 0; i--)
		adjustHeap(heap, size, i);
}

/**
* Adds an element to the heap.
* @param heap
* @param value  value to be added to heap.
* @param compare  pointer to compare function.
*/
void dyHeapAdd(DynamicArray* heap, TYPE value){
	assert(heap != 0);
	int parent, pos;
	dyAdd(heap, value);
	pos = dySize(heap) - 1;
	while (pos != 0){
		parent = (pos - 1) / 2;
		if (compare(dyGet(heap, pos)->d, dyGet(heap, parent)->d) == -1){
			dySwap(heap, pos, parent);
			pos = parent;
		}
		else
			return;
	}
}

/**
* Removes the first element, which has the small priority, form the heap.
* @param heap
* @param compare  pointer to the compare function.
*/
void dyHeapRemoveMin(DynamicArray* heap){
	assert(heap != 0);
	int last = dySize(heap) - 1;
	assert(dySize(heap) != 0);
	struct Wrestler* min = dyGet(heap, 0); // get the min node
	dyPut(heap, dyGet(heap, last), 0); // Copy the last element into the first position
	delete min; // free up memory allocated for min node
	dyRemoveAt(heap, last); // Remove last element
	adjustHeap(heap, last, 0); // perculate the value down into position to fix the heap ordering
}

/**
* Returns the first element, which has the small priority, from the heap.
* @param heap
* @return  Element at the top of the heap.
*/
TYPE dyHeapGetMin(DynamicArray* heap){
	assert(heap != 0);
	assert(dySize(heap) != 0);
	return dyGet(heap, 0); // return the root's value
}

/**
* Sorts arbitrary array in-place.
* @param heap  array with elements in arbitrary order.
* @param compare  pointer to the compare function.
*/
void dyHeapSort(DynamicArray* heap){
	buildHeap(heap);
	for (int i = dySize(heap) - 1; i >= 0; i--){
		dySwap(heap, 0, i); // exchange the root value with the value at index i
		adjustHeap(heap, i, 0); // perculate the value down into position to fix the heap ordering
	}
}

// --- Utility ---

void dyPrint(DynamicArray* array){
	cout << "size: " << dySize(array) << "\ncapacity: " << array->capacity << "\n";
	for (int i = 0; i < dySize(array); i++){
		cout << dyGet(array, i)->d << " ";
		cout << dyGet(array, i)->i << "\n";
	}
	cout << "\n";
}

