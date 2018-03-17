/*
 * DynamicArray.hpp
 *
 *  Created on: Feb 17, 2018
 *      Author: Jonathan Perry
 */

#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include "BFS.hpp"
#define TYPE struct Wrestler*

typedef struct DynamicArray DynamicArray;
struct DynamicArray;

int compare(int, int);

DynamicArray* dyNew(int);
void dyDelete(DynamicArray*);

// Dynamic array
void dyAdd(DynamicArray*, TYPE);
void dyAddAt(DynamicArray*, TYPE, int);
void dyPut(DynamicArray*, TYPE, int);
void dyRemoveAt(DynamicArray*, int);
TYPE dyGet(DynamicArray*, int);
int dySize(DynamicArray*);
int dyCap(DynamicArray*);
void dySwap(DynamicArray*, int, int);

int binarySearch(DynamicArray* array, int value);
// Heap
void dyHeapAdd(DynamicArray*, TYPE);
void dyHeapRemoveMin(DynamicArray*);
TYPE dyHeapGetMin(DynamicArray*);
void dyHeapSort(DynamicArray*);


// Utility
/**
 * Prints the size, capacity, and elements of array, calling the print
 * function on each element.
 * @param array
 * @param print
 */
void dyPrint(DynamicArray*);

#endif
