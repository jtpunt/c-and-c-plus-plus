#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;


vector<int> findMode(int[], int);

int main()
{
	int myArray[] = { 20, 4, 0, 0, 4, 7, 8, 9, 20 };
	int arraySize1 = sizeof(myArray) / sizeof(myArray[0]);
	vector<int> modes = findMode(myArray, arraySize1);
	cout << "The modes:" << endl;
	for (size_t i = 0; i < modes.size(); i++) {
		cout << modes[i] << "  ";
	}
}