/*
 * BFS.cpp
 *
 *  Created on: Feb 16, 2018
 *      Author: Jonathan Perry
 */
#include "BFS.hpp"
#include<bits/stdc++.h>
#include <vector>
#include <iostream>
using std::cout;
using std::vector;
/**************************************************************************
 * param: d - distance
 * param: i - original index before being sorted
 * post: d and i are assigned
 * ret: pointer to struct Wrestler is returned
 ***************************************************************************/
struct Wrestler* newWrestler(int d, int i){
	struct Wrestler* wrestler = new Wrestler;
	wrestler->d = d;
	wrestler->i = i;
	return wrestler;
}
/**************************************************************************
 * param: distances - vector which contains distances obtained from running BFS
 *        starting at the 1st source vertex. Each index in distance corresponds
 *        to a wrestler in the vector wrestlers, and contains the distance away
 *        from the 1st source vertex.
 * post: 0 is stored in every index
 ***************************************************************************/
void initializeDistance(vector<int> &distance){
	for(int i = 0; i < distance.size(); i++){
		distance[i] = 0;
	}
}
/**************************************************************************
 * param: heap - pointer to binary heap
 * post: wrestler with both d and i as 0 is added onto the heap as the first
 *       element.
 * post: the rest of the wrestlers are added onto the heap with d as INT_MAX
 ***************************************************************************/
void initializeQueue(DynamicArray* heap){
	dyAdd(heap, newWrestler(0, 0));
	for(int i = 1; i < dyCap(heap); i++){
		dyAdd(heap, newWrestler(INT_MAX, i));
	}
}
/**************************************************************************
 * param: heap - pointer to binary heap
 * param: adjList - address to a 2D vector which will contain the rivarlry arrangement
 *        where each value stored refers to an index from the wrestlers vector
 * param: distances - vector which contains distances obtained from running BFS
 *        starting at the 1st source vertex. Each index in distance corresponds
 *        to a wrestler in the vector wrestlers, and contains the distance away
 *        from the 1st source vertex.
 * post: Starts at the first vertex in the list and discovers every vertex that is
 *       reachable from there and marking the distances traveled from the first vertex.
 ***************************************************************************/
void BFS(DynamicArray* heap, vector<vector<int> > &adjList, vector<int> &distance){
	while(dySize(heap) != 0){
		struct Wrestler* u = dyHeapGetMin(heap);
		for(int i = 1; i < adjList[u->i].size(); i++){
			int index = binarySearch(heap, adjList[u->i][i]); // check to see if the adjacent vertex is still in the queue
			if(distance[adjList[u->i][i]] == 0 && index != 0){ // if distance is equal to 0, then the node has not been visited
				distance[adjList[u->i][i]] = distance[u->i] + 1; // update distances
				dyGet(heap, index)->d = distance[adjList[u->i][i]];
			}
		}
		u = nullptr;
		dyHeapRemoveMin(heap);
	}
}
