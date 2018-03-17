/*
 * circularList.hpp
 *
 *  Created on: Feb 22, 2018
 *  	Project: CS 325 Traveling Salesman Problem
 *      Author: Jonathan Perry, David Ramirez, Armand Reitz
 */
#ifndef CIRCULARLIST_HPP_
#define CIRCULARLIST_HPP_
template<typename T>
class CircularList{
	private:
		struct Link{
			Link(T value) : value(value), next(nullptr), prev(nullptr) {}
			T value;
			Link* next;
			Link* prev;
		};
		int size;
		Link* frontSentinel = nullptr;
		Link* backSentinel = nullptr;
	public:
		CircularList();
		CircularList(T);
		int getSize();
		void circularListDestroy();
		void addLinkAfter(Link* link, T value);
		void removeLink(Link* link);
		void print();
		void reverse();

		// Deque interface

		void addFront(T);
		void addBack(T);
		Link* getFront();
		Link* getBack();
		void removeFront();
		void removeBack();
		bool isEmpty();
};

#include "circular_impl.hpp"
#endif /* CIRCULARLIST_HPP_ */
