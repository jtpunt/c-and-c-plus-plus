/*
 * main.cpp
 *
 *  Created on: Feb 16, 2018
 *      Author: Jonathan Perry
 */
#include "DynamicArray.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include<bits/stdc++.h>
#include <string>
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
/**************************************************************************
 * param: ioFile - pointer to ifstream object
 * param: content - address to wrestlers or rivalries vector
 * post:  Each line in the file is pushed into the wrestlers or rivalries vector
 ***************************************************************************/
void readLine(ifstream& ioFile, vector<string> &content){
	string line;
	while (getline(ioFile, line)){
		if(line.size() && line[line.size()-1] == '\r') // carriage return symbol found?
			line = line.substr(0, line.size() - 1); // remove carriage return symbol
		content.push_back(line);
	}
}
/**************************************************************************
 * param: fileName - contains the name of the file we are reading
 * param: wrestlers - pointer to vector of strings which will hold the wrestler's
 *        names.
 * param: rivalries - pointer to vector of strings which will hold a pair of wrestler's
 *        names who are rivals.
 * post:  Each line in the file is pushed into the wrestlers and rivalries vector
 ***************************************************************************/
void readFile(string fileName, vector<string> &lines){
	ifstream ioFile;
	ioFile.open(fileName.c_str());
	if (ioFile.fail())
		cout << "The file failed to open: " << endl;
	else{
		readLine(ioFile, lines);
	}
	ioFile.close(); // Close the file
}
struct City{
	int city_id;
	int x_cord;
	int y_cord;
	int d;
};
struct City* newCity(int city_id, int x_cord, int y_cord, int d){
	struct City* city = new City;
	city->city_id = city_id;
	city->x_cord = x_cord;
	city->y_cord = y_cord;
	city->d = d;
	return city;
}
int main(){
//	vector<string> lines;
//	readFile("test.txt", lines);
//	cout << lines.size() << " size\n";
//	for(int i = 0; i < lines.size(); i++){
//		cout << lines[i] << "\n";
//	}
	DynamicArray<City*> myArray(4);
	myArray.dyHeapAdd(newCity(0, 0, 0, 5));
	myArray.dyHeapAdd(newCity(1, 1, 1, 4));
	myArray.dyHeapAdd(newCity(2, 2, 2, 3));
	myArray.dyHeapAdd(newCity(3, 3, 3, 2));
	myArray.dyHeapAdd(newCity(4, 4, 4, 0));
	myArray.dyHeapAdd(newCity(5, 5, 5, 7));
	myArray.dyPrint();
	myArray.dyHeapRemoveMin();
	myArray.dyPrint();
//	DynamicArray<int> myArray(4);
//	myArray.dyHeapAdd(4);
//	myArray.dyHeapAdd(3);
//	myArray.dyHeapAdd(2);
//	myArray.dyHeapAdd(1);
//	myArray.dyPrint();
//	cout << myArray.binarySearch(myArray.dyGet(3)) << "\n"; // 4
//	cout << myArray.binarySearch(myArray.dyGet(2)) << "\n"; // 3
//	cout << myArray.binarySearch(myArray.dyGet(1)) << "\n"; // 2
//	cout << myArray.binarySearch(myArray.dyGet(0)) << "\n"; // 1
	//cout << myArray.binarySearch(myArray.dyGet(5)) << "\n"; // error
//	DynamicArray<char> myString(4);
//	myString.dyAdd('h');
//	myString.dyAdd('t');
//	myString.dyAdd('l');
//	myString.dyPrint();
	return 1;
}



