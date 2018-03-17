/*
 * BFS.hpp
 *
 *  Created on: Feb 16, 2018
 *      Author: Jonathan Perry
 */

#ifndef BFS_HPP_
#define BFS_HPP_
#include "DynamicArray.hpp"
#include <vector>
struct Wrestler{
	int d;
	int i;
};
struct DynamicArray;
struct Wrestler* newWrestler(int, int);
void initializeDistance(std::vector<int> &);
void initializeQueue(DynamicArray*);
void BFS(DynamicArray* heap, std::vector<std::vector<int> > &, std::vector<int> &);

#endif /* BFS_HPP_ */
