/*
 * DynamicArray.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: Jonathan Perry
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>
using std::cout;

auto compare = [](auto left, auto right){
	if(left < right)
		return -1;
	else if(left > right)
		return 1;
	else
		return 0;
};

template <typename T>
DynamicArray<T>::DynamicArray(int capacity){
	cout << "in dynamicarray constructor\n";
	assert(capacity > 0);
	data = nullptr;
	size = 0;
	setCapacity(capacity);
}
//template <typename T>
//DynamicArray<T>::~DynamicArray(){
//	delete [] data;
//}
//template <typename T>
//int DynamicArray<T>::compare(T left, T right){
//	if(left < right)
//		return -1;
//	else if(left > right)
//		return 1;
//	else
//		return 0;
//}

// --- Dynamic array ---
template <typename T>
void DynamicArray<T>::setCapacity(int cap){
	T* oldBuffer = data;
	data = new T[cap];
	for(int i = 0; i < size; i++)
		data[i]  = oldBuffer[i];
	delete [] oldBuffer;
	capacity = cap;
}
template <typename T>
void DynamicArray<T>::dyAdd(T value){
	if (size >= capacity){
		cout << "size >= capacity\n";
		setCapacity(2 * capacity);
	}
	dyPut(value, dySize());
	size++;
}
template <typename T>
void DynamicArray<T>::dyAddAt( T value, int position){
	assert(position <= size);
	dyAdd(value);
	for (int i = dySize() - 1; i > position; i--){
		dySwap(i, i - 1);
	}
}
template <typename T>
void DynamicArray<T>::dyPut(T value, int position){
	assert(position <= size);
	cout << "in dyPut..\n";
	data[position] = value;
}
template <typename T>
void DynamicArray<T>::dyRemoveAt(int position){
	assert(position < dySize());
	for (int i = position; i < dySize() - 1; i++){
		dyPut(dyGet(position + 1), position); // slide values to the left
	}
	size--;
}
template <typename T>
T DynamicArray<T>::dyGet(int position){
	assert(position <= dySize());
	return data[position];
}

template <typename T>
int DynamicArray<T>::dySize(){
	return size;
}
template <typename T>
int DynamicArray<T>::dyCap(){
	return capacity;
}
template <typename T>
void DynamicArray<T>::dySwap(int position1, int position2){
	assert(position1 <= dySize());
	assert(position2 <= dySize());
	cout << " in dySwap\n";
	T temp = data[position1];
	dyPut(dyGet(position2), position1);
	dyPut(temp, position2);
}


template <typename T>
int DynamicArray<T>::binarySearch(T value){
	int low = 0;
	int high = dySize();
	while (low <= high){
		int middle = (low + high) / 2;
		if (compare(value->city_id, dyGet(middle)->city_id) < 0){
			high = middle - 1;
		}
		else if (compare(value->city_id, dyGet(middle)->city_id) > 0){
			low = middle + 1;
		}
		else{
			return middle;
		}
	}
	return low;
}

// --- Heap ---
template <typename T>
int DynamicArray<T>::indexSmallest(int i, int j){
	cout << i << " compared to " << j << "\n";
	cout << dyGet(i)->d << " < " << dyGet(j)->d << "\n";
	if(dyGet(i)->d < dyGet(j)->d){
		return i;
	}
	return j;
}
/**
* Adjusts heap to maintain the heap property.
* @param heap
* @param last  index to adjust up to.
* @param position  index where adjustment starts.
* @param compare  pointer to compare function.
*/
template <typename T>
void DynamicArray<T>::adjustHeap(int last, int position){
	int small;
	int left = (2 * position) + 1;
	int right = (2 * position) + 2;
	cout << "in adjustHeap: last = " << last << "\n";
	if (right < last){
		cout << "right < last\n";
		small = indexSmallest(left, right);
		if (compare(dyGet(small)->d, dyGet(position)->d) == -1){
			cout << dyGet(small)->d << " small compared to position " << dyGet(position)->d << "\n";
			dySwap(position, small);
			adjustHeap(last, small);
		}
	}
	else if (left < last){
		cout << "left < last\n";
		if (compare(dyGet(left)->d, dyGet(position)->d) == -1){
			cout << dyGet(left)->d << "left compared to position " << dyGet(position)->d << "\n";
			dySwap(position, left);
			adjustHeap(last, left);
		}
	}
}

/**
* Builds a valid heap from an arbitrary array.
* @param heap  array with elements in any order.
* @param compare  pointer to compare function.
*/
template <typename T>
void DynamicArray<T>::buildHeap(){
//	assert(heap != 0);
	int size = dySize();
	for (int i = dySize() / 2 - 1; i >= 0; i--)
		adjustHeap(size, i);
}

/**
* Adds an element to the heap.
* @param heap
* @param value  value to be added to heap.
* @param compare  pointer to compare function.
*/
template <typename T>
void DynamicArray<T>::dyHeapAdd(T value){
//	assert(heap != 0);
	int parent, pos;
	cout << "creating node value..\n";
	dyAdd(value);
	pos = dySize() - 1;
	while (pos != 0){
		cout << "in while loop\n";
		parent = (pos - 1) / 2;
		if (compare(dyGet(pos)->d, dyGet(parent)->d) == -1){
			cout << "going to dySwap\n";
			dySwap(pos, parent);
			pos = parent;
		}
		else{
			cout << "returning..\n";
			return;
		}
	}
}

/**
* Removes the first element, which has the small priority, form the heap.
* @param heap
* @param compare  pointer to the compare function.
*/
template <typename T>
void DynamicArray<T>::dyHeapRemoveMin(){
//	assert(heap != 0);
	assert(dySize() != 0);
	int last = dySize() - 1;
	dyPut(dyGet(last), 0); // Copy the last element into the first position
	dyRemoveAt(last); // Remove last element
	adjustHeap(last, 0); // perculate the value down into position to fix the heap ordering
}

/**
* Returns the first element, which has the small priority, from the heap.
* @param heap
* @return  Element at the top of the heap.
*/
template <typename T>
T DynamicArray<T>::dyHeapGetMin(){
//	assert(heap != 0);
	assert(dySize() != 0);
	return dyGet(0); // return the root's value
}

/**
* Sorts arbitrary array in-place.
* @param heap  array with elements in arbitrary order.
* @param compare  pointer to the compare function.
*/
template <typename T>
void DynamicArray<T>::dyHeapSort(){
	buildHeap();
	for (int i = dySize() - 1; i >= 0; i--){
		dySwap(0, i); // exchange the root value with the value at index i
		adjustHeap(i, 0); // perculate the value down into position to fix the heap ordering
	}
}

// --- Utility ---
//template <typename T>
//void DynamicArray<T>::dyPrint(){
//	cout << "size: " << dySize() << "\ncapacity: " << capacity << "\n";
//	for (int i = 0; i < dySize(); i++){
//		cout << dyGet(i) << "\n";
//	}
//	cout << "\n";
//}
template <typename T>
void DynamicArray<T>::dyPrint(){
	cout << "size: " << dySize() << "\ncapacity: " << capacity << "\n";
	for (int i = 0; i < dySize(); i++){
		cout << dyGet(i)->city_id << " ";
		cout << dyGet(i)->x_cord << " ";
		cout << dyGet(i)->y_cord << " ";
		cout << dyGet(i)->d << "\n";
	}
	cout << "\n";
}
