/*********************************************************************
* Author: Jonathan Perry
* Date: 1/27/2018
* Description: This file contains code for reading every line as a string
* from a file called "act.txt", extracting integers from each of those
* lines read in, and outputting the number of activities selected and
* their order to the terminal.
*********************************************************************/
#include "activity-Selector.hpp"
#include <fstream>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
/**************************************************************************
 * param: fileContent - contains a single line from amount.txt
 * post:  All integers in the string are converted and stored in a vector
 *        of integers
 * ret: The vector of integers is returned
 ***************************************************************************/
vector<int> convertString(string fileContent){
	string multiDigits;
	vector<int> digits;
	int digit;
	int length = fileContent.length();
	for(int i = 0; i < length; i++){
		// If the character is a space, skip it and move on
		if(fileContent[i] == ' '){}
		else{
			// Keep looping over the characters to read in possible multi-digit integers
			while(fileContent[i] != ' ' && i != length){
				multiDigits += fileContent[i];
				i++;
			}
			// convert the string into an integer
			digit  = stoi(multiDigits);
			digits.push_back(digit);
			multiDigits = ""; // clear the string so we can read in the next integer
		}
	}
	return digits;
}
/**************************************************************************
 * param: fileName - contains the name of the file we are reading
 * param: content - pointer to a vector of strings which holds each line from
 * 		  the text file
 * post:  Each line in the file is pushed into a vector that stores strings
 ***************************************************************************/
void readFile(string fileName, vector<string> *content){
	ifstream ioFile;
	string line;
	ioFile.open(fileName.c_str());
	if (ioFile.fail()){
		cout << "The file failed to open: " << endl;
	}
	else{
		while (getline(ioFile, line)){
			(*content).push_back(line);
		}
	}
	ioFile.close(); // Close the file
}
/**************************************************************************
 * param: parent - 2d array of all activities in the current set
 * param: child - 1d array of the current line of integers being copied into
 * 	      the 2d parent array
 * post: The current line of integers from the 1d child array is pushed into
 * 		 the 2d parent array
 ***************************************************************************/
void copyArray(vector<vector<int> > &parent, vector<int> child, int row){
	int size = child.size();
	for(int i = 0; i < size; i++){
		parent.at(row).push_back(child[i]);
	}
}
/**************************************************************************
 * param: v1 - vector of strings containing every line from act.txt
 * param: v2 - address to a 2d array to store the first set of activities
 * param: v2 - address to a 2d array to store the second set of activities
 * param: v2 - address to a 2d array to store the third set of activities
 * post: Each 2d array is resized according to the number of activities listed
 *       in v1
 * post: Each 2d array is filled with set data, including the activitity number,
 *       the activities start time, and the activities finish time.
 ***************************************************************************/
void createSets(vector <string> v1, vector<vector<int> > &v2, vector<vector<int> > &v3, vector<vector<int> > &v4){
	vector<int> temp;
	int count = 0;
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	for(int i = 0; i < v1.size(); i++){
		temp = convertString(v1[i]);
		if(temp.size() == 1){ // line that has the amount of activities in each set
			count++;
			if(count == 1){
				v2.resize(temp[0]); // set size of v2
			}
			else if(count == 2){
				v3.resize(temp[0]); // set size of v3
			}
			else{
				v4.resize(temp[0]); // set size of v4
			}
		}
		else{
			if(count == 1){
				copyArray(v2, temp, index1++);
			}
			else if(count == 2){
				copyArray(v3, temp, index2++);
			}
			else{
				copyArray(v4, temp, index3++);
			}
		}
	}
}
/**************************************************************************
 * param: vec - 1d array of activities selected in decreasing order
 * post: 1d array of activities is printed to the console in increasing order
 ***************************************************************************/
void printVector(vector<int> vec){
	for (int i = vec.size() - 1; i >= 0; i--){
		cout << vec[i] << " ";
	}
	cout << "\n";
}

/**************************************************************************
 * param: selectedActivities - 1d array of activities selected in decreasing order
 * param: set - the set number of activities being selected from
 * post: The set number, number of activities selected, and each individual activity
 * 		 in increasing order are all printed to the terminal.
 ***************************************************************************/
void outputResults(vector<int> selectedActivities, int set){
	cout << "Set " << set << "\n";
	cout << "Number of activities selected = " << selectedActivities.size() << "\n";
	cout << "Activities ";
	printVector(selectedActivities);
	cout << "\n\n";
}
int main(){
	vector <string> v1;
	vector<int> temp;
	vector<vector<int> > v2, v3, v4;

	readFile("act.txt", &v1);
	createSets(v1, v2, v3, v4);

	outputResults(activitySelector(v2), 1);
	outputResults(activitySelector(v3), 2);
	outputResults(activitySelector(v4), 3);
	return 0;
}



