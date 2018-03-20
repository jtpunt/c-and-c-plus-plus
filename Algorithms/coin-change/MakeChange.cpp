/*********************************************************************
** Author: Jonathan Perry
** Date: 1/27/2018
** Description: This file contains the implementation code of the
** makeChange algorithm
*********************************************************************/
#include "MakeChange.hpp"
using std::vector;
/**************************************************************************
 * param: v - 2d vector which holds the minimum coin arrangements for values
 * 		  1..A
 * param: row1 - the row which we are taking coin column data from, where each
 * 	      column keeps a tally on how many coins were used
 * param: row2 - the row which we are adding coin column data from row1 from
 * post:  all columns from row1 are copied into row2
 ***************************************************************************/
void addVector(vector<vector<int> > &v, int row1, int row2){
	for(int col = 0; col < v[row2].size(); col++){
		v[row2][col] = v[row1][col];
	}
}
/***************************************************************************
 *  param: V - vector of coins of some denomination
 *  param: A - the amount of change we are asked to make
 *  param: C - address to a vector with size [0..V.size()-1]. C[i] is the #
 *         of coins of value[i]
 *  post: coinCount has rows[0..A] initialized, where A is our value we need
 *  	  minimum change for.
 *  post: coinCount has columns [0..V.size()-1] initialized, where each column
 *  	  corresponds to a coin in vector V. Each column keeps a tally on the
 *  	  # of coins used to make change for the current row number between
 *  	  [0..V.size()-1].
 *  post: the minimum number of coins needed is calculated for each value from
 *   	  1..A and is stored in the vector coinCount and the minimum number of
 *   	  coins need for A is stored in the vector C.
 *  ret:  value stored at min_coins[A] - the minimum # of coins needed to make
 *        change for value A.
 ***************************************************************************/
int makeChange(vector <int> V, int A, vector<int> &C){
	// min_coins keeps track of the minimum # of coins needed for each value from 0..A
	vector <int> min_coins(A+1, A+1);
	vector <vector<int> > coinCount(A+1, vector<int>(V.size(), 0));
    	min_coins[0] = 0; // 0 coins means 0 change
    	// Loop through all values from 1 to A
	for(int cur_val=1; cur_val<=A; cur_val++){
		// Loop through all coins in V
		for(int j = V.size() - 1; j >= 0; j--){
			// See if the value of the coin in V is less than i
			if(V[j] <= cur_val){
				// coins_needed = the minimum number of coins required to make the value
				int coins_needed = min_coins[cur_val-V[j]] + 1;
				// if i - V[j] = 0, then 0 coins are needs
				// if i - V[j] > 0, then more coins are needed
				if(coins_needed < min_coins[cur_val]){
					min_coins[cur_val] = coins_needed;
					addVector(coinCount, cur_val-V[j], cur_val);
					coinCount[cur_val][j]++;
				}
			}
		}
	}
	for(int i = 0; i < V.size(); i++){
		C.push_back(coinCount[A][i]);
	}
	return min_coins[A];
}

