/*********************************************************************
** Author: Jonathan Perry
** Date: 5/28/2017
** Description: This file contains the class specification of the
** variables and functions needed for searching for a value in a text
** file through both a linear search algorithm and a binary search algorithm.
** After reading the text files for the first time, values from the files are
** stored in 2 designated vectors (1 contains the original data, the other
** vector contains the sorted integers) - which are both used to perform
** the binary search. After the vectors are sorted, the program prompts
** the user to enter in the name of the output file they wish to save
** the sorted values into.
*********************************************************************/
#ifndef SEARCHALGORITHM_HPP
#define SEARCHALGORITHM_HPP
#include <vector>
#include <string>
class searchAlgorithm
{
private:
	// Vector of integers that will be sorted by a bubble sort algorithm
	std::vector<int> file1;
	std::vector<int> file2;
	std::vector<int> file3;
	std::vector<int> file4;
	// Vectors of integers that don't get sorted
	std::vector<int> originalFile1;
	std::vector<int> originalFile2;
	std::vector<int> originalFile3;
	std::vector<int> originalFile4;
public:
	searchAlgorithm(){}
	void searchValue(int);
	bool readFile(std::string, int, std::vector<int>&, std::vector<int>&);
	void searchValueResults(bool, int);

	void startSort();
	void sortValues(std::vector<int>&);
	void outputIntegers(std::vector<int>);

	void startBinarySearch(int);
	int binarySearch(std::vector<int>, int);
	void binarySearchResults(int);

};
#endif // !SEARCHALGORITHM_HPP
