/*
 * main.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: jonathan
 */
#include "insertionsort.hpp"
#include "mergesort.hpp"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using std::ifstream;
using std::ofstream;
using std::copy;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

void printVector(vector <int> v){
	for (unsigned int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}
void readFile(string fileName, vector <int> &v1, vector <int> &v2, vector <int> &v3){
	ifstream ioFile;

	bool firstNumber = true;
	bool firstArray = true;
	bool secondArray = false;

	int integer, arr_size, numsRead = 0;
	ioFile.open(fileName.c_str());
	if (ioFile.fail())
		cout << "The file failed to open: " << endl;
	else{
		while (ioFile >> integer){
			// firstNumber in the text file indicates the size of the array to be read in
			if(firstNumber){
				arr_size = integer;
				cout << "size of array: " << integer << endl;
				cout << "contents of array: " << endl;
				firstNumber = false;
			}
			else if(numsRead < arr_size){
				cout << integer << " ";
				if(firstArray)
					v1.push_back(integer);
				else if(secondArray)
					v2.push_back(integer);
				else
					v3.push_back(integer);
				numsRead++;
				if(numsRead == arr_size){
					firstNumber = true; // set to true to read integer in for the second array
					if(firstArray){
						firstArray = false; // set to false to push integers into the second array
						secondArray = true;
					}
					else if(secondArray){
						secondArray = false;
					}
					numsRead = 0;
					cout << endl << endl;
				}
			}
		}
	}
	ioFile.close(); // Close the file
}
void writeFile(string filename, vector <int> v1, vector <int> v2, vector <int> v3){
	ofstream myFile;
	myFile.open(filename.c_str());
	if(myFile.fail()){
		cout << "The file failed to open: " << endl;
	}else{
		for(int i = 0; i < v1.size(); i++){
			myFile << v1[i] << " ";
		}
		myFile << "\n";
		for(int i = 0; i < v2.size(); i++){
			myFile << v2[i] << " ";
		}
		myFile << "\n";
		for(int i = 0; i < v3.size(); i++){
			myFile << v3[i] << " ";
		}
		myFile << "\n";
	}
	myFile.close();
}
int main(){
	vector <int> ins1, ins2, ins3, merge1, merge2, merge3;

	// Insertion Sort Code
	readFile("data.txt", ins1, ins2, ins3);

	cout << "Running Insertion Sort on first vector" << endl;
	insertionSort(ins1);
	printVector(ins1);

	cout << "Running Insertion Sort on second vector" << endl;
	insertionSort(ins2);
	printVector(ins2);

	cout << "Running Insertion Sort on third vector" << endl;
	insertionSort(ins3);
	printVector(ins3);

	writeFile("insert.out", ins1, ins2, ins3);

	// Merge Sort Code
	readFile("data.txt", merge1, merge2, merge3);

	cout << "Running Merge Sort on first vector" << endl;
	insertionSort(merge1);
	printVector(merge1);

	cout << "Running Merge Sort on second vector" << endl;
	insertionSort(merge2);
	printVector(merge2);

	cout << "Running Merge Sort on third vector" << endl;
	insertionSort(merge3);
	printVector(merge3);

	writeFile("insert.out", merge1, merge2, merge3);
    return 0;
}


