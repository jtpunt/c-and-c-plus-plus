/*
 * main.cpp
 *
 *  Created on: Feb 16, 2018
 *  	Project: CS 325 Traveling Salesman Problem
 *      Author: Jonathan Perry
 */
#include "circularList.hpp"
#include <fstream>   // std::ifstream, std::ofstream
#include <sstream>   // std::stringstream
#include <limits>    // std::numeric_limits
#include <iostream>  // std::cout
#include <string>    // std::string
#include <cmath>     // std::sqrt, std::pow
#include <algorithm> // std::copy, std::sort, std::for_each
#include <vector>    // std::vector
#include <chrono>    // std::chrono::high_resolution_clock
using std::chrono::high_resolution_clock;
using std::numeric_limits;
using std::string;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::for_each;
typedef high_resolution_clock Clock;

struct City{
	City(): city_id(0), x_coord(0), y_coord(0) { }
	int city_id;
	int x_coord;
	int y_coord;
};
/**************************************************************************
 * param: city_id - city_id read in from the current line that was processed
 * param: x_coord - x_coord read in from the current line that was processed
 * param: y_coord - y_coord read in from the current line that was processed
 * post:  New City object is dynamically allocated with the members
 *        set to the values passed in.
 * ret:   Pointer to newly created City structure is returned.
 ***************************************************************************/
struct City* newCity(int city_id,int x_coord,int y_coord){
	struct City *city = new City;
	city->city_id = city_id;
	city->x_coord = x_coord;
	city->y_coord = y_coord;
	return city;
}
void printCities(vector<City*> &cities){
	for (auto it: cities){
		cout << it->city_id << " " << it->x_coord << " " << it->y_coord << "\n";
	}
}
/**************************************************************************
 * param: ioFile - pointer to ifstream object
 * param: cities - address to cities vector
 * post:  Each city_id, x_coord, y_coord is extracted from each line and stored
 *        into local variables.
 * post:  Each local variable is used to initialize a new City object by calling
 *        the newCity function, which returns a pointer to that new City object.
 * post:  The pointer to the new City object is pushed into the cities vector.
 ***************************************************************************/
void readLine(ifstream& ioFile, vector<City*> &cities){
	string line;
	while(getline(ioFile, line)){
		stringstream ss(line);
		int city_id, x_coord, y_coord;
		if(ss >> city_id >> x_coord >> y_coord){
			cities.push_back(newCity(city_id, x_coord, y_coord));
		}
	}
	cout << "returning from readLine..\n";
}
/**************************************************************************
 * param: ioFile   - pointer to ifstream object
 * param: fileName - contains the name of the file we are reading
 * param: cities - address to cities vector
 * post:  pointers to ioFile ifstream object and cities vector are used to
 *        call the readLine function to extract the city_id, x_coord, and
 *        y_coord data from each line.
 ***************************************************************************/
void openFile(ifstream& ioFile, string fileName , vector<City*> &cities){
	string line;
	ioFile.open(fileName.c_str());
	if (ioFile.fail()){
		cout << "The file failed to open: \n";
	}
	else{
		readLine(ioFile, cities);
	}
}
/*******************************************************************************************************
 * Returns the next bins that should be explored based on the current bin of the city just traveled to.
 * Because the cities were sorted in ascending order based on their distance from x,y point (0,0),
 * we can assume that we only need to look at 3 of the 4 bins that contain cities that are close by.
 *   For example: If the current city that was just traveled to was found in bin 1, we should only look at
 *   bins 0, 1, and 2 to find the next shortest path. The shortest path would not be found from a city in
 *   bin 3, as bin 3 contain cities that are much further away from bin 1.
 * The bin of the current city just traveled to should also be the first bin to explore for the next shortest path
 * since it contains cities with similar distances from x,y point (0,0)
 ********************************************************************************************************/
vector<int> getBinIndices(int current_bin){
	switch(current_bin){
		case 0: return {0, 1, 3};
		case 1: return {1, 2, 0};
		case 2: return {2, 3, 1};
		case 3: return {3, 0, 2};
	}
}
/*******************************************************************************************************
 * Returns the next bins that should be explored based on the current bin of the city just traveled to.
 * If the next bins that are going to be explored are empty, return every single bin number. The function
 * getNextCity will loop through the empty bins until it finds a bin that contains cities.
 ********************************************************************************************************/
template<typename T>
vector<int> getNextBins(const vector<CircularList<T>*> &bins, int current_bin){
	vector<int> bin_indices = getBinIndices(current_bin);
	if(bins[bin_indices[0]]->isEmpty() || bins[bin_indices[1]]->isEmpty() || bins[bin_indices[2]]->isEmpty()){
		bin_indices = {0, 1, 2, 3};
	}
	return bin_indices;
}
/**************************************************************************************
 * Returns the starting city's city_id, x-coord, y-coord, and the bin it was found in.
 *************************************************************************************/
template<typename T>
int getStartingCity(vector<CircularList<T>*> &bins, vector<City*> &visited_cities, int start){
	int bin = 0;
	for(auto it : bins){
		auto current = it->getFront();
		for(int i = 0; i < it->getSize(); i++){
			if(current->value->city_id == start){
				visited_cities.push_back(current->value);
				bins[bin]->removeLink(current);
				return bin;
			}
			current = current->next;
		}
		bin++;
	}
	return bin;
}
/******************************************************************
 * Returns the Euclidean distance between the two cities.
 *****************************************************************/
int calculateDistance(const City* c1, const City* c2){
	int xSquared = pow((float)(c1->x_coord - c2->x_coord), 2);
	int ySquared = pow((float)(c1->y_coord - c2->y_coord), 2);
	return (floor((float) (sqrt(xSquared + ySquared)) + 0.5));
}
/*****************************************************************************************
* Binary comparison function used in the sort algorithm. Accepts two pointers to two
* different cities, and compares the cities to their distance from x,y point 0,0 so that
* the sort algorithm sorts them in ascending order by their distance from x,y point 0,0.
*****************************************************************************************/
bool byDistance(const City* c1, const City* c2){
	City point0 = City();
	int c1Distance = calculateDistance(&point0, c1);
	int c2Distance = calculateDistance(&point0, c2);
	return c1Distance < c2Distance;
}
/*****************************************************************************************
 * Binary comparison function used in the sort algorithm. Accepts two pointers to two
 * different cities, and compares the cities to their city_id so that the sort algorithm
 * sorts them in ascending order by city_id.
 *****************************************************************************************/
bool byCityID(const City *c1, const City* c2){
	return c1->city_id < c2->city_id;
}
/* ****************************************************************************************
 * Sort cities in ascending order based on their distance from x,y point 0,0, and
 * then sort each quarter separately in the list in ascending order based on their city_id.
 * etc, a list with 20 cities:
 * [1....5] contains city_ids: 5, 7, 8, 11, 12
 * [6...10] contains city_ids: 4, 6, 9, 10, 18
 * [11..15] contains city_ids: 2, 3, 14, 16, 17
 * [16..20] contains city_ids: 1, 13, 15, 19, 20
 *****************************************************************************************/
void sortCities(vector<City*> &cities){
	sort(cities.begin(), cities.end(), byDistance);
	sort(cities.begin(), cities.begin() + cities.size()/4, byCityID);                                      // 1st quarter
	sort(cities.begin() + cities.size()/4, cities.begin() + cities.size()/2, byCityID);                    // 2nd quarter
	sort(cities.begin() + cities.size()/2, cities.begin() + cities.size()/2 + cities.size()/4, byCityID);  // 3rd quarter
	sort(cities.begin() + cities.size()/2 + cities.size()/4, cities.end(), byCityID);                      // 4th quarter
}
/*************************************************************************************
 * Adds n/4 cities into their corresponding bin number, where the key is their city_id,
 * and their value is the x-coord and y-coord.
 *************************************************************************************/
template<typename T>
void addCities(CircularList<T> *bins, vector<City*> &cities, vector<City*>::iterator begin, vector<City*>::iterator end){
	vector<City*>::iterator it;
	for(auto it = begin; it < end; it++){
		bins->addBack(*it);
	}
}
/*****************************************************************************************************
 * Explores 3 out of 4 bins (approximately 75% of available cities) at a time to find the next shortest
 * path that can be taken. When a shortest path is found, the distance, key, and bin number of the
 * corresponding city is saved. Each minimum distance is compared to other city candidates that may be
 * the final shortest path that can be taken. Finally, the key of the city along with the bin it resides
 * in is returned.
 *******************************************************************************************************/
template<typename T>
int getNextCity(const vector<CircularList<T>*> &bins, const vector<int> &bin_nums, const City* start, vector<int> &distance, vector<City*> &visited_cities){
	int minWeight = numeric_limits<int>::max();
	City* city = nullptr;
	int bin_idx = 0;
	auto minCity = bins[bin_nums[0]]->getFront();
	for(auto bin_num: bin_nums){
		auto current = bins[bin_num]->getFront();
		for(int i = 0; i < bins[bin_num]->getSize(); i++){
			int dist = calculateDistance(start, current->value);
			if(dist < minWeight){
				minWeight = dist;
				city = current->value;
				minCity = current;
				bin_idx = bin_num;
			}
			current = current->next;
		}
	}
	bins[bin_idx]->removeLink(minCity);
	visited_cities.push_back(city);
	distance.push_back(minWeight);
	return bin_idx;
}
/* ******************************************************************************************************
 * Greedy Traveling Sales Problem Algorithm: Makes the locally optimum choice at each stage by selecting
 * the city nearest to the current city the algorithm is at, as to minimize total distance traveled.
 *******************************************************************************************************/
template<typename T>
int greedy_tour(vector<CircularList<T>*> &table, int size, vector<City*> &visited_cities, int start_city){
	int sum = 0;
	int currentBin = getStartingCity(table, visited_cities, start_city);
	T start = visited_cities.back();
	vector<int> distance;
	for(int i = 0; i < size - 1; i++){
		vector<int> bins = getNextBins(table, currentBin);
		currentBin = getNextCity(table, bins, start, distance, visited_cities);
		start = visited_cities.back();
	}
	for_each(distance.begin(), distance.end(), [&] (int n) {
	    sum += n;
	});

	return sum + calculateDistance(visited_cities.back(), visited_cities.front());
}
/*************************************************************
 * Frees all the memory allocated for each city in the vector.
 *************************************************************/
void deallocateCities(vector<City*> &cities){
	for(auto city: cities){
		delete city;
		city = nullptr;
	}
}
/*************************************************************
 * Goes through each bin and frees all the memory allocated for
 * each link structure containing a city structure in the linked
 * list,then frees the memory allocated for the linked list structure.
 *************************************************************/
void deallocateBins(vector<CircularList<City*>*> &bins){
	for(auto bin: bins){
		bin->circularListDestroy();
		delete bin;
		bin = nullptr;
	}
	bins.clear();
}
/***********************************************************************
 * Adds the cities into their bins after they have been first sorted.
 * Each bin contains cities that have similar distances from x,y point 0,0.
 **********************************************************************/
void packBins(vector<CircularList<City*>*> &bins, vector<City*> &cities){
	deallocateBins(bins);
	for(int i = 0; i < 4; i++){ // create 4 circularList structures
		bins.push_back(new CircularList<City*>()); // pointers to 4 of the created circularList structures
	}
	addCities(bins[0], cities, cities.begin(), cities.begin() + cities.size()/4);
	addCities(bins[1], cities, cities.begin() + cities.size()/4, cities.begin() + cities.size()/2);
	addCities(bins[2], cities, cities.begin() + cities.size()/2, cities.begin() + cities.size()/2 + cities.size()/4);
	addCities(bins[3], cities, cities.begin() + cities.size()/2 + cities.size()/4, cities.end());
}
/***********************************************************************
 * Any cities still in the cities vector has their memory freed before
 * resetting the cities vector, so that it contains 0 elements.
 * Then, each city within the citiesCpy vector is copied into the cities
 * vector by allocating separate memory for each city. This is done so that
 * the cities/citiesCpy vector don't have pointers to the same cities. This
 * allows brute force on all different permutations of cities we can start
 * with, since this function allows for resetting the cities back to the
 * same values it originally had.
 ***********************************************************************/
void makeCpyCities(vector<City*> &cities, vector<City*> &citiesCpy){
	deallocateCities(cities);
	cities.clear();
	for(auto city: citiesCpy){
		cities.push_back(newCity(city->city_id, city->x_coord, city->y_coord));
	}
}
/**************************************************************************
 * param: myFile 		 - pointer to ofstream object
 * param: filename 		 - contains the name of the file we are writing to
 * param: visited_cities - vector of cities in the order they were visited in
 * param: distance       - the total distance traveled by visiting each city
 *                         within the vector visited_cities.
 * post:  fileName, denominations, amount, coinsUsed, and minCoins are written
 * 		  to the name of the file that was sent in.
 ***************************************************************************/
void outputResults(ofstream& myFile, string filename, vector<City*> &visited_cities, int &distance){
	myFile.open(filename.c_str(), ofstream::trunc);
	if(myFile.fail()){
		cout << "The file failed to open: \n";
	}
	else{
		myFile << distance << "\n";
		for(auto city: visited_cities){
			myFile << city->city_id << "\n";
		}
	}
}
/***********************************************************************
 * This functions tries all cities as a possible candidate to start at for
 * finding the shortest route which visits each city once and then returns
 * back to the original city that the function started at. If starting at
 * the current city candidate results in a total distance that is less than
 * the current known minimum distance traveled, then the path taken to obtain
 * this distance is saved into the visited_cities_min vector, and the minimum
 * distance traveled is updated.
 **********************************************************************/
vector<City*> bruteForceTour(vector<CircularList<City*>*> &bins, vector<City*> &cities, int start, int end, int &min_distance){
	vector<City*> citiesCpy;
	vector<City*> visited_cities;
	vector<City*> visited_cities_min;
	min_distance = numeric_limits<int>::max();
	makeCpyCities(citiesCpy, cities);
    	for(int i = start; i <= end; i++){
    		cout << "\nstarting at city " << i << "\n";
    		int distance = greedy_tour(bins, cities.size(), visited_cities, i);
    		cout << distance << "\n";
    		if(distance < min_distance){
    			cout << " distance < min_distance with city " << i << "\n";
    			min_distance = distance; // update min distance traveled
    			// deallocate memory in visited_cities_min and then copy tour details from visited_cities into visited_cities_min
    			makeCpyCities(visited_cities_min, visited_cities);
    		}
    		visited_cities.clear(); // reset visited_cities for next tour
    		packBins(bins, citiesCpy); // deallocate current memory in bins and reset bins for next tour
    	}
    	deallocateCities(cities);
    	deallocateCities(citiesCpy);
    	deallocateBins(bins);
    	return visited_cities_min;
}
int main(int argc, char* argv[]){
	if (argc != 2){
		cout << "Only 1 argument needed. Please try again.\n";
	    	exit(1);
	}
	vector<City*> cities;
	vector<City*> visited_cities_min;
	vector<CircularList<City*>*> bins;  // Pointers to circularList class, which contains pointers to city structures
	string fileName = argv[1];
	ofstream myFile;
	int distance = 0;



	ifstream ioFile;
	openFile(ioFile, fileName, cities);
	ioFile.close();

	sortCities(cities);
	packBins(bins, cities);

	auto clock_start = Clock::now();
	//    visited_cities_min = bruteForceTour(bins, cities, 0, cities.size() - 1, distance); // brute force on cities 0 to cities.size() - 1
	visited_cities_min = bruteForceTour(bins, cities, 11, 11, distance); // single tour on just city 11
	auto clock_end = Clock::now();

	outputResults(myFile, fileName + ".tour", visited_cities_min, distance);
	myFile.close();
    	deallocateCities(visited_cities_min);
    	cout << fileName << " took " << std::chrono::duration_cast<std::chrono::duration<float>>(clock_end - clock_start).count() << " sec\n";


	return 0;
}



