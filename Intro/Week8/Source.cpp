#include <iostream>
#include "Student.hpp"
using namespace std;

const int SIZE = 10;
double stdDev(const Student *array, int size);
int main()
{
	Student student1("John", 1);
	Student student2("Jacob", 2);
	Student student3("Peter", 3);
	Student student4("Parker", 4);
	Student student5("Smith", 5);
	Student student6("Bob", 6);
	Student student7("Bob", 7);
	Student student8("Bob", 8);
	Student student9("Bob", 9);
	Student student10("Bob", 10);

	Student studentArray[SIZE] = { student1, student2, student3, student4, student5, student6, student7, student8, student9, student10 };

	cout << stdDev(studentArray, SIZE) << endl;
}