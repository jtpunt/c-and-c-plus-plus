/*********************************************************************
** Author: Jonathan Perry
** Date: 1/21/2018
** Description: This file contains code for reading data for 3 vectors
** from a text file, code writing the content of those 3 vectors to a file
** called "stooge.out", code printing the contents of the vector to the
** console, and code for generating set amount of random numbers and storing
** each number in a single vector.
*********************************************************************/
#include "StoogeSort.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
// Prints all the contents of the vector to the console
void printVector(vector <int> v){
	for (unsigned int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}
// Takes in 3 vectors and fills them with data from a specified file name
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
// Takes in 3 vectors and writes each of their content to a specified file name
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
// Generates an (size) amount of random numbers between 1-10000 and stores them in the vector that was sent in
void generateNumbers(vector <int> &v, int size){
	srand((unsigned)time(NULL));
	for(int i = 0; i < size; i ++){
		// generate a random # between 1-10000 and store it in the vector
		v.push_back(rand() % 10000 + 1);
	}
}
int main(){
//	vector <int> v;
//	generateNumbers(v, 10000);
//	clock_t timer = clock();
//	StoogeSort(v, 0, v.size()- 1);
//	timer = clock() - timer;
//	cout << "StoogeSort took " << (float)timer / (float)CLOCKS_PER_SEC << " seconds.";
	vector <int> v1, v2, v3;
	readFile("data.txt", v1, v2, v3);

	cout << "Running StoogeSort on first vector" << endl;
	StoogeSort(v1, 0, v1.size() - 1);
	printVector(v1);

	cout << "Running StoogeSort on first vector" << endl;
	StoogeSort(v2, 0, v2.size() - 1);
	printVector(v2);

	cout << "Running StoogeSort on first vector" << endl;
	StoogeSort(v3, 0, v3.size() - 1);
	printVector(v3);
	writeFile("stooge.out", v1, v2, v3);
    return 0;
}

