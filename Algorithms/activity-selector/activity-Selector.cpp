/*********************************************************************
* Author: Jonathan Perry
* Date: 1/27/2018
* Description: This file contains the implementation code of the
* activity selector algorithm
*********************************************************************/
#include "activity-Selector.hpp"
using std::vector;
/**************************************************************************
 * param: activities - address to a 2d array which contains the set of activities
 * post:  the 2d array is sorted in increasing order based on each activities
 *        start time
 * post:  activities are selected from the last activity to start that are all
 * 		  compatible with all previously selected activities
 ***************************************************************************/
vector<int> activitySelector(vector<vector<int> > &activities){
	insertionSort(activities);
	int n = activities.size();
	vector<int> A(1); // set of activities being select
	A[0] = activities[n - 1][0]; // greedy select - last activity with the last start time is selected
	int i = n - 1;
	for(int m = n - 2; m >= 0; m--){ // loop through each activity from n-2 ... 0
		if(activities[m][2] <= activities[i][1]){ // activity[m][finish] <= activity[i][start]
			A.push_back(activities[m][0]); // store the activity #
			i = m; // new activity, move forward
		}
	}
	return A;
}
/**************************************************************************
 * param: activities - address to a 2d array which contains the set of activities
 * post:  the 2d array is sorted in increasing order based on each activities
 *        start time
 ***************************************************************************/
void insertionSort(vector<vector<int>> &activities){
	int key_a, key_s, key_f, j;
	for(int i = 1; i < activities.size(); i++){
		key_a = activities[i][0]; // activity #
		key_s = activities[i][1]; // start time
		key_f = activities[i][2]; // finish time
		j = i - 1;
		while(j >= 0 && activities[j][1] > key_s){
			activities[j+1][0] = activities[j][0]; // activity #
			activities[j+1][1] = activities[j][1]; // start time
			activities[j+1][2] = activities[j][2]; // finish time
			j--;
		}
		activities[j+1][0] = key_a; // activity #
		activities[j+1][1] = key_s; // start time
		activities[j+1][2] = key_f; // finish time
	}
}
