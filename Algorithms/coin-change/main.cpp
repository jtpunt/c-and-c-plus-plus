/*********************************************************************
** Author: Jonathan Perry
** Date: 1/27/2018
** Description: This file contains code for reading every line as a string
** from a file called "amount.txt", extracting integers from each of those
** lines read in, and writing to file named "change.txt" which contains
** the denomination set, the amount we needed change for, the arrangement
** of coins used to make that amount, and the minimum number of coins used.
*********************************************************************/
#include "MakeChange.hpp"
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
 *        of integers.
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
 * 		  the text file.
 * post:  Each line in the file is pushed into a vector that stores strings.
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
 * param: filename - contains the name of the file we are writing to
 * param: denominations - the set of coins used
 * param: amount - the value we need exact change for
 * param: coinsUsed - vector which contains the minimum arrangement of coins
 * 		  that were used, which equals the amount variable passed in
 * param: minCoins - how many coins were used to equal the amount variable
 * post:  fileName, denominations, amount, coinsUsed, and minCoins are written
 * 		  to the name of the file that was sent in.
 ***************************************************************************/
void writeFile(string filename, string denominations, string amount, vector<int> coinsUsed, int minCoins){
	ofstream myFile;
	myFile.open(filename.c_str(), ofstream::app);
	if(myFile.fail()){
		cout << "The file failed to open: " << endl;
	}else{
		myFile << denominations << "\n";
		myFile << amount << "\n";
		for(int i = 0; i < coinsUsed.size(); i++){
			myFile << coinsUsed[i] << " ";
		}
		myFile << "\n" << minCoins << "\n";
	}
	myFile.close();
}
int main(){
	vector <string> v1;
	vector <int> C1, C2, C3, C4;
	int min1, min2, min3, min4;
	readFile("amount.txt", &v1);
	min1 = makeChange(convertString(v1[0]), convertString(v1[1])[0], C1);
	min2 = makeChange(convertString(v1[2]), convertString(v1[3])[0], C2);
	min3 = makeChange(convertString(v1[4]), convertString(v1[5])[0], C3);
	min4 = makeChange(convertString(v1[6]), convertString(v1[7])[0], C4);
	writeFile("change.txt", v1[0], v1[1], C1, min1);
	writeFile("change.txt", v1[2], v1[3], C2, min2);
	writeFile("change.txt", v1[4], v1[5], C3, min3);
	writeFile("change.txt", v1[6], v1[7], C4, min4);
}



