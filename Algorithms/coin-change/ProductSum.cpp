/*
 * ProductSum.cpp
 *
 *  Created on: Jan 23, 2018
 *      Author: jonathan
 */
#include "ProductSum.hpp"
#include <iostream>
using std::vector;
using std::cout;
/**********************************************************************************************
 * Given a list of n integers, v 1 , . . . , v n , the product-sum is the largest sum that can
 * be formed by multiplying adjacent elements in the list. Each element can be matched with at
 * most one of its neighbors. For example, given the list 4, 3, 2, 8 the product sum is
 * 28 = (4 × 3) + (2 × 8), and given the list 2, 2, 1, 3, 2, 1, 2, 2, 1, 2 the product sum is
 * 19 = (2 × 2) + 1 + (3 × 2) + 1 + (2 × 2) + 1 + 2.
 **********************************************************************************************/
//int productSum(vector <int> v){
//	int sum = 0;
//	for(int i = v.size() -1; i >= 0; i--){
//		cout << "loop #" << i << "\n";
//		if(v[i] == 1)
//			sum += 1;
//		else{ // v[i] is not equal to 1
//			// add the product of v[i] and v[i-1] to sum if v[i-1] != 1 and when i is not -1
//			if(v[i - 1] != 1 && i - 1 != -1){
//				sum += (v[i] * v[i-1]);
//				i--; // decrement i so we don't encounter v[i-1] again in the for loop
//			}
//			else // v[i - 1] is equal to 1, we must add it
//				sum += v[i];
//		}
//		//cout << "sum is : " << sum << "\n";
//	}
//	return sum;
//}
//int max(int a, int b) { return a > b? a: b;}
//int productSum(vector <int> v, int n){
//	if(n == 0)
//		return 0;
//	vector <int> OPT(n+1);
//	OPT[0] = 0;
//	OPT[1] = v[0];
//	for(int i = 2; i <= n; i++){
//		cout << "OPT[" << i << "-1](" << OPT[i-1] << ") + v[" << i << "-1](" << v[i-1] << ") = " << OPT[i-1] + v[i-1] << "\n";
//		cout << "OPT[" << i << "-2](" << OPT[i-2] << ") + v[" << i << "-1](" << v[i-1] << ") * " << "v[" << i << "-2]("<< v[i-2] << ") = "<< OPT[i-2] + (v[i-1] * v[i-2]) << "\n";
//
//		OPT[i] = max(OPT[i-1] + v[i-1], OPT[i-2] + v[i-1] * v[i-2]);
//		cout << "OPT[" << i << "] = " << OPT[i] << "\n\n";
//	}
//	for(int i = 0; i < OPT.size(); i++){
//		cout << OPT[i] << "\n";
//	}
//	return OPT[n];
//}
//int main(){
//	vector <int> v{ 2, 1, 3, 5, 1, 4, 2 };
//	//cout << "vector size: " << v.size() << "\n";
//	cout << "\n" << productSum(v, v.size()) << "\n";
//	//cout << "\n" << productSum(v) << "\n";
//	return 1;
//}
