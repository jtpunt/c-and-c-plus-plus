/*
 * knapsack.cpp
 *
 *  Created on: Feb 9, 2018
 *      Author: jonathan
 */
#include <vector>
#include <iostream>
#include <iomanip>
using std::setw;
using std::cout;
using std::vector;
void displayVector(vector<vector<int> > vec){
	cout << setw(9) << "weight-->";
	for(int i = 0; i < vec.size(); i++){
		cout << i << " ";
	}
	cout << "\n " << setw(9);
	for(int i = 0; i < vec.size(); i++){
		cout << "__";
	}
	cout << "\n";
	for (int i = 0; i < vec.size(); i++){
		cout << "item: " << i << " |";
	    for (int j = 0; j < vec[i].size(); j++){
	        cout << vec[i][j] << " ";
	    }
	    cout << "\n";
	}
}
void knapsack(vector<int> &weights, vector<int> &benefits, int W){
	// benefits[0..size-1]
	// weights[0..size-1]
	// must subtract i by 1 for the current item, or a whole item will be skipped
	vector <vector<int> > OPT(benefits.size()+1, vector<int>(W+1, 0));
	// Base cases 0 weight = 0 value. 0 benefits = 0 value
	for(int i = 1; i <= benefits.size(); i++){ // loop through each item
		for(int w = 1; w <= W; w++){ // grow the weight of the knapsack
			if(weights[i-1] <= w){ // item i-1 can be apart of the solution
				// current item's benefits + OPT of prev item (if is room for it) > OPT of prev item at current weight w
				if(benefits[i-1] + OPT[i-1][w-weights[i-1]] > OPT[i-1][w])
					OPT[i][w] = benefits[i-1] + OPT[i-1][w-weights[i-1]];
				else // don't use the current item
					OPT[i][w] = OPT[i-1][w];
			}
			else // item i-1 cannot be apart of the solution, it is too big
				OPT[i][w] = OPT[i-1][w]; // use the OPT obtained from the previous item with the current weight
		}
	}
	displayVector(OPT);
}

int main(){
	vector<int> weights = {1, 2, 3, 4, 5};
	vector<int> benefits = {2, 3, 4, 5, 6};
	knapsack(weights, benefits, 5);
}


