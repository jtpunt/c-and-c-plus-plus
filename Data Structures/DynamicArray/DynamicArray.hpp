/*
 * DynamicArray.hpp
 *
 *  Created on: Feb 17, 2018
 *      Author: Jonathan Perry
 */

#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

template<typename T>
class DynamicArray{
	private:
		T* data;
		int size;
		int capacity;
	public:
		DynamicArray(int);
//		~DynamicArray();
//		int compare(T, T);
		void setCapacity(int);

		// Dynamic array
		void dyAdd(T);
		void dyAddAt(T, int);
		void dyPut(T, int);
		void dyRemoveAt(int);
		T dyGet(int);
		int dySize();
		int dyCap();
		void dySwap(int, int);

		int binarySearch(T value);
		// Heap
		int indexSmallest(int, int);
		void adjustHeap(int, int);
		void buildHeap();
		void dyHeapAdd(T);
		void dyHeapRemoveMin();
		T dyHeapGetMin();
		void dyHeapSort();
		void dyPrint();
};
#include "Dyn_impl.hpp"
#endif
