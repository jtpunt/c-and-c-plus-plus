/*
 * main.cpp
 *
 *  Created on: Feb 16, 2018
 *      Author: Jonathan Perry
 */
#include "DynamicArray.hpp"
#include "BFS.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
/**************************************************************************
 * param: wrestlers - vector of strings which contains the wrestlers names
 * post: Each wrestler's name is searched for and has their index returned
 * ret: index which contain's the wrestler's name
 ***************************************************************************/
int searchVector(vector<string> wrestlers, string search){
	for(int i = 0; i < wrestlers.size(); i++){
		if(wrestlers[i] == search)
			return i;
	}
}
/**************************************************************************
 * param: wrestlers - vector of strings which contains the wrestlers names
 * param: rivalries - vector of strings which contains the pair of rivalries
 * param: adjList - address to a 2D vector which will contain the rivarlry arrangement
 *        where each value stored refers to an index from the wrestlers vector
 * post:  Each pair of wrestlers is extracted and stored in individual strings
 * post: Each wrestler's name is searched for and has their index returned
 * post: The index for the first wrestler is pushed into the row that contains the
 *       index for the second wrestler.
 * post: The index for the second wrestler is pushed into the row that contains the
 *       index for the first wrestler.
 ***************************************************************************/
void buildAdjList(vector<string> wrestlers, vector<string> rivalries, vector<vector<int> > &adjList){
	string str1, str2;
	for(int i = 0; i < adjList.size(); i++){
		adjList[i].push_back(i);
	}
	for(int i = 0; i < rivalries.size(); i++){
		int pos = rivalries[i].find(' ');
		str1 = rivalries[i].substr(0, pos);
		str2 = rivalries[i].substr(pos+1);
		// undirected graph, so both wrestlers point to each other
		adjList[searchVector(wrestlers, str1)].push_back(searchVector(wrestlers, str2));
		adjList[searchVector(wrestlers, str2)].push_back(searchVector(wrestlers, str1));
	}
}
/**************************************************************************
 * param: ioFile - pointer to ifstream object
 * param: content - address to wrestlers or rivalries vector
 * post:  Each line in the file is pushed into the wrestlers or rivalries vector
 ***************************************************************************/
void readLine(ifstream& ioFile, vector<string> &content){
	int num = 0; // n - number of wrestlers, or r - number of rivalries
	string line;
	ioFile >> num; // stores the # of wrestlers, or # of rivalries
	content.reserve(num);
	getline(ioFile,line); // skips to the next line, or a blank line will be read in
	for(int i = 0; i < num; i++){
		getline(ioFile,line);
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
void readFile(string fileName, vector<string> &wrestlers, vector<string> &rivalries){
	ifstream ioFile;
	ioFile.open(fileName.c_str());
	if (ioFile.fail())
		cout << "The file failed to open: " << endl;
	else{
		readLine(ioFile, wrestlers);
		readLine(ioFile, rivalries);
	}
	ioFile.close(); // Close the file
	cout << "file closed..\n";
}
/**************************************************************************
 * param: distances - vector which contains distances obtained from running BFS
 *        starting at the 1st source vertex. Each index in distance corresponds
 *        to a wrestler in the vector wrestlers, and contains the distance away
 *        from the 1st source vertex.
 * param: wrestlers - vector of strings which contains the wrestler's names
 * post:  evenCount is incremented by 1 for each even distance
 * post:  heels has all wrestlers with even distances added to it
 * post:  babyfaces  has all wrestlers with odd distances added to it
 * post:  heels and babyfaces are outputted to the console when evenCount is
 *        equal to oddCount
 ***************************************************************************/
void postResults(vector<int> distances, vector<string> wrestlers){
	string heels, babyfaces;
	int oddCount  = 0,
	    evenCount = 0;
	for(int i = 0; i < distances.size(); i++){
		if(distances[i] % 2 == 0){
			evenCount++;
			babyfaces += wrestlers[i] + " ";
		}
		else{
			oddCount++;
			heels += wrestlers[i] + " ";
		}
	}
	if(oddCount == evenCount){
		cout << "Yes. Possible\n";
		cout << "Babyfaces : " << babyfaces << "\n";
		cout << "Heels : " << heels << "\n";
	}
	else
		cout << "Impossible\n";
}
int main(){
	vector<string> wrestlers;
	vector<string> rivalries;
	string fileName;
	do{
	    cout << "Enter the file name: (wrestler.txt, wrestler1.txt, wrestler2.txt)";
	    getline(std::cin, fileName);
	}while(fileName != "wrestler.txt" && fileName != "wrestler1.txt" && fileName != "wrestler2.txt");
	readFile(fileName, wrestlers, rivalries);

	vector<vector <int> > adjList(wrestlers.size());
	vector<int> distance(wrestlers.size());

	buildAdjList(wrestlers, rivalries, adjList);


	DynamicArray* queue = dyNew(wrestlers.size());
	initializeQueue(queue);
	initializeDistance(distance);

	BFS(queue, adjList, distance);
	dyDelete(queue);

	postResults(distance, wrestlers);
	return 1;
}



