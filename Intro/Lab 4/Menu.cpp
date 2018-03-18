/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This file contains the implentation code of the
** variables and functions needed for creating and managing an information
** system for a university by adding and deleting students, instructors,
** and buildings in real time.
*********************************************************************/
#include "Menu.hpp"
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;                                                                        
using std::setw;
using std::getline;
using std::ofstream;
using std::ifstream;
using std::string;
using std::vector;
using std::shared_ptr;
/*********************************************************************
** Description: This is the default constructor which creates instantiates
** 1 student, 1 instructor, and 2 buildings und
*********************************************************************/
Menu::Menu()
{
	addUniversity("Oregon State University");
	// Create base pointer to the University Object
	University* univ = getUniversity("Oregon State University");

	addStudent("Jonathan Perry", 23);
	addBuilding("Adams Hall", 11168, "606 SW 15TH STCORVALLIS, OR 97331");
	addBuilding("Aero Engineering Lab", 3637, "852 SW 30TH STREET CORVALLIS, OR 97331");
	addInstructor("Luyao Zhang", 30);
	Student *student = getStudent("Jonathan Perry");
	displayMenu();
	delete univ;
}
/*********************************************************************
** Description: This is a function resets any error flags for cin
** and discards up to 1,000 characters from the input buffer.
*********************************************************************/
void Menu::correctInput()
{
	// resets any error flags for cin if anything but integers are entered
	cin.clear();
	// Discards up to 1,000 characters from the input buffer or until a newline is read
	cin.ignore(1000, '\n');
}
/*********************************************************************
** Description: This is a function that prints out the menu to the current
** users to give them options on navigating through the program.
*********************************************************************/
void Menu::displayMenu()
{
	int menuChoice = 0, menuChoice2 = 0, menuChoice3 = 0, menuChoice4 = 0, input = 0, studentAge = 0, personAge = 0, instructorAge = 0, buildingSize = 0;
	string personName = "", buildingName = "", studentName = "", instructorName = "", buildingAddress = "";
	cout << "____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Show building information:                             |" << endl;
	cout << "|2. Show all people information:                           |" << endl;
	cout << "|3. Choose a person to do work:                            |" << endl;
	cout << "|4. Add/Delete Building                                    |" << endl;
	cout << "|5. Add/Delete Student                                     |" << endl;
	cout << "|6. Add/Delete Instructor                                  |" << endl;
	cout << "|7. Exit                                                   |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		// Displays the name, size and address of each building
		cout << setw(25) << "Building Name:" << setw(12) << "Size:" << setw(45) << "Address:" << endl;
		// Loops through every building in the vector and send all attributes to University method print_Building_Info
		for (auto i : buildings)
		{
			i->print_Building_Info(i->getName(), i->getSize(), i->getAddress());
		}
		cout << "\n";
		displayMenu();
		break;
	case 2:
		// Displays the name, size and address of every student
		cout << setw(25) << "Student Name:" << setw(5) << "Age:" << setw(8) << "GPA:" << setw(16) << "Homework Hours:" << endl;
		// Loops through every student in the vector and send all attributes to University method print_People_Info
		for (auto i : students)
		{
			i->print_People_Info(i->getName(), i->getAge(), i->getGPA(), i->getHW_Hours());
		}
		cout << "\n";
		// Displays the name, size and address of every instructor
		cout << setw(25) << "Instructor Name:" << setw(5) << "Age:" << setw(8) << "Rating:" << setw(16) << "Grading Hours:" << endl;
		// Loops through every instructor in the vector and send all attributes to University method print_People_Info
		for (auto i : instructors)
		{
			i->print_People_Info(i->getName(), i->getAge(), i->getRating(), i->getGradingHours());
		}
		cout << "\n";
		displayMenu();
		break;
	case 3:
		// Show the user all students and instructors
		listStudents();
		cout << "\n";
		listInstructors();
		cout << "\n";
		cout << "Enter in the full name of a student or instructor to do work: ";
		correctInput();
		getline(cin, personName);

		// Make sure the name of the student or instructor they entered exists
		if (getStudent(personName) == NULL && getInstructor(personName) == NULL)
		{
			cout << "Student or instructor not found: " << endl;
		}
		// An instructor or student exists at this point
		// Check to see they're an instructor and not a student
		else if (getStudent(personName) == NULL)
		{
			// Creates People base pointer to the instructor (derived) object
			People *base = getInstructor(personName);
			cout << "Please enter in any number to generate a random number that reprsents how many hours they will do work for : ";
			cin >> input;
			while (!cin)
			{
				cout << "Please enter in an integer: ";
				correctInput();
				cin >> input;
			}
			// Calls the Instructor virtual function do_work 
			base->do_work(input);
		}
		// Check to see they're an student and not a instructor
		else if (getInstructor(personName) == NULL)
		{
			// Creates People base pointer to the student (derived) object
			People *base = getStudent(personName);
			cout << "Please enter in any number to generate a random number that reprsents how many hours they will do work for : ";
			cin >> input;
			while (!cin)
			{
				cout << "Please enter in an integer: ";
				correctInput();
				cin >> input;
			}
			// Calls the student virtual function do_work
			base->do_work(input);
		}
		displayMenu();
		break;
	case 4:
		listBuildings();
		cout << "\n1. Add a Building: " << endl;
		cout << "2. Delete a Building: " << endl;
		cout << "3. Go Back: " << endl;
		cout << "Enter a number to get started: ";
		cin >> menuChoice2;
		correctInput();
		if (menuChoice2 == 1)
		{
			cout << "Enter in the name of the new building: ";
			getline(cin, buildingName);
			cout << "Enter in the size of the new building: ";
			cin >> buildingSize;
			correctInput();
			cout << "Enter in the address of the new building: ";
			getline(cin, buildingAddress);
			addBuilding(buildingName, buildingSize, buildingAddress);
		}
		else if (menuChoice2 == 2)
		{
			cout << "Enter in the name of the building you wish to delete: ";
			getline(cin, buildingName);
			removeBuilding(buildingName);
		}
		else
		{
			cout << "Going back to main menu: " << endl;
		}
		displayMenu();
		break;
	case 5:
		listStudents();
		cout << "\n1. Add a Student: " << endl;
		cout << "2. Delete a Student: " << endl;
		cout << "3. Go Back: " << endl;
		cout << "Enter a number to get started: ";
		cin >> menuChoice3;
		correctInput();
		if (menuChoice3 == 1)
		{
			cout << "Enter in the name of the new student: ";
			getline(cin, studentName);
			cout << "Enter in the age of the new student: ";
			cin >> studentAge;
			correctInput();
			addStudent(studentName, studentAge);
		}
		else if (menuChoice3 == 2)
		{
			cout << "Enter in the name of the student you wish to delete: ";
			getline(cin, studentName);
			removeStudent(studentName);
		}
		else
		{
			cout << "Going back to main menu: " << endl;
		}
		displayMenu();
		break;
	case 6:
		listInstructors();
		cout << "\n1. Add a Instructor: " << endl;
		cout << "2. Delete a Instructor: " << endl;
		cout << "3. Go Back: " << endl;
		cout << "Enter a number to get started: ";
		cin >> menuChoice4;
		correctInput();
		if (menuChoice4 == 1)
		{
			cout << "Enter in the name of the new instructor: ";
			getline(cin, instructorName);
			cout << "Enter in the age of the new instructor: ";
			cin >> instructorAge;
			correctInput();
			addInstructor(instructorName, instructorAge);
		}
		else if (menuChoice4 == 2)
		{
			cout << "Enter in the name of the instructor you wish to delete: ";
			getline(cin, instructorName);
			removeInstructor(instructorName);
		}
		else
		{
			cout << "Going back to main menu: " << endl;
		}
		displayMenu();
		break;
	case 7:
		break;
	default:
		correctInput();
		cout << "Invalid input entered, please try again: " << endl;
		displayMenu();
		break;
	}
}
/*********************************************************************
** Description: This is a non-member function which receives
** returns a string in all lowercase characters.
*********************************************************************/
string toLowercase(string str)
{
	for (int i = 0; str[i]; i++)
	{
		// converts search word to lowercase
		str[i] = tolower(str[i]);
	}
	return str;
}
/*********************************************************************
** Description: This is function that receives a name of a new University
** to create a new university object dynamically and store the object
** in a vector of pointers to university objects if the university doesn't
** already exist.
*********************************************************************/
bool Menu::addUniversity(string name)
{
	if (getUniversity(name) == NULL)
	{
		universities.push_back(new University(name));
		return true;
	}
	else
	{
		cout << "The university " << name << " already exists!" << endl;
		return false;
	}
}
/*********************************************************************
** Description: This is function that receives a name of a University
** and if a matching University name is found, it then removes that University
** object from the vector of pointers to Building objects and then deallocates
** space used for that object.
*********************************************************************/
bool Menu::removeUniversity(string name)
{
	University* univToRemove = getUniversity(name);
	if (univToRemove != NULL)
	{
		universities.erase(remove(universities.begin(), universities.end(), univToRemove), universities.end());
		delete univToRemove;
		return true;
	}
	else
	{
		cout << "The university " << name << " cannot be found!" << endl;
		return false;
	}
}
/*********************************************************************
** Description: This is a function that displays every University stored
** in the vector if the vector is not empty. 
*********************************************************************/
void Menu::listUniversities()
{
	if (universities.empty())
	{
		cout << "No Universities Found: " << endl;
	}
	else
	{
		cout << "Universities:" << endl;
		for (auto i : universities)
		{
			cout << i->getName() << endl;
		}
	}
}
/*********************************************************************
** Description: This is method that receives the name of a University
** and then loops through a vector of pointers to university objects to
** find and return a university object with a matching name.
*********************************************************************/
University* Menu::getUniversity(string name)
{
	name = toLowercase(name);
	for (auto i : universities)
	{
		string universityName = toLowercase(i->getName());
		if (universityName.find(name)!= string::npos)
		{
			return i;
		}
	}
	return NULL;
}
/*********************************************************************
** Description: This is function that receives a name of a new Building
** to create a new building object dynamically and store the object
** in a vector of pointers to building objects if the building doesn't
** already exist.
*********************************************************************/
bool Menu::addBuilding(string name, int size, string address)
{
	if (getBuilding(name) == NULL)
	{
		univ = new Buildings(name, size, address);
		Buildings* building = static_cast<Buildings*>(univ);
		buildings.push_back(building);
		return true;
	}
	else
	{
		cout << "The building " << name << " already exists!" << endl;
		return false;
	}
}
/*********************************************************************
** Description: This is function that receives a name of a Building
** and if a matching Building name is found, it then removes that Building 
** object from the vector of pointers to Building objects and then deallocates 
** space used for that object. 
*********************************************************************/
bool Menu::removeBuilding(string name)
{
	Buildings* buildingToRemove = getBuilding(name);
	if (buildingToRemove != NULL)
	{
		buildings.erase(remove(buildings.begin(), buildings.end(), buildingToRemove), buildings.end());
		delete buildingToRemove;
		return true;
	}
	else
	{
		cout << "The building " << name << " could not be found!" << endl;
		return false;
	}
	return true;
}   
/*********************************************************************
** Description: This is a function that displays the name, size and address 
** of every Building stored in the vector of pointers to Building objects 
** if the vector is not empty.
*********************************************************************/
void Menu::listBuildings()
{
	cout << setw(25) << "Building Name:" << setw(12) << "Size:" << setw(45) << "Address:" << endl;
	for (auto i : buildings)
	{
		cout << setw(25) << i->getName() << setw(10) << i->getSize() << setw(45) << i->getAddress() << endl;
	}
}
/*********************************************************************
** Description: This is method that receives the name of a Building
** and then loops through a vector of pointers to building objects to 
** find and return a building object with a matching name.
*********************************************************************/
Buildings* Menu::getBuilding(string name)
{
	name = toLowercase(name);
	for (auto i : buildings)
	{
		string buildingName = toLowercase(i->getName());
		if (buildingName.find(name) != string::npos)
		{
			return i;
		}
	}
	return NULL;
}
/*********************************************************************
** Description: This is function that receives a name and age of a new Student
** to create a new student object dynamically and store the object
** in a vector of pointers to student objects if the student doesn't 
** already exist.
*********************************************************************/
bool Menu::addStudent(string name, int age)
{
	if (getStudent(name) == NULL)
	{
		univ = new Student(name, age);
		Student* student = static_cast<Student*>(univ);
		students.push_back(student);
		return true;
	}
	else
	{
		cout << "The student " << name << " already exists!" << endl;
		return false;
	}
}
/*********************************************************************
** Description: This is function that receives a name, age, gpa and 
** homework hours completed of a new Student to create a new student 
** object dynamically and store the object in a vector of pointers to 
** student objects if the student doesn't already exist.
*********************************************************************/
bool Menu::addStudent(string name, int age, double gpa, int hwHours)
{
	if (getStudent(name) == NULL)
	{
		univ = new Student(name, age, gpa, hwHours);
		Student* student = static_cast<Student*>(univ);
		students.push_back(student);
		return true;
	}
	else
	{
		cout << "The student " << name << " already exists!" << endl;
		return false;
	}
}
/*********************************************************************
** Description: This is function that receives a name of a Student
** and if a matching student name is found, it then removes that Student
** object from the vector of pointers to Student objects and then deallocates
** space used for that object.
*********************************************************************/
bool Menu::removeStudent(string name)
{
	Student* StudentToRemove = getStudent(name);
	if (StudentToRemove != NULL)
	{
		students.erase(remove(students.begin(), students.end(), StudentToRemove), students.end());
		delete StudentToRemove;
		return true;
	}
	else
	{
		cout << "The student " << name << " could not be found!" << endl;
		return false;
	}
	return true;
}
/*********************************************************************
** Description: This is a function that displays the name, age, gpa, and 
** homework hours completed of every Student stored in the vector of 
** pointers to Student objects if the vector is not empty.
*********************************************************************/
void Menu::listStudents()
{
	if (students.empty())
	{
		cout << "No Students Found: " << endl;
	}
	else
	{
		cout << setw(25) << "Student Name:" << setw(5) << "Age:" << setw(8) << "GPA:" << setw(16) << "Homework Hours:" << endl;
		for (auto i : students)
		{
			cout << setw(25) << i->getName() << setw(5) << i->getAge() << setw(8) << i->getGPA() << setw(8) << i->getHW_Hours() << endl;
		}
	}
}
/*********************************************************************
** Description: This is method that receives the name of a Student
** and then loops through a vector of pointers to student objects to
** find and return a student object with a matching name.
*********************************************************************/
Student* Menu::getStudent(string name)
{
	name = toLowercase(name);
	for (auto i : students)
	{
		string studentName = toLowercase(i->getName());
		if (studentName.find(name) != string::npos)
		{
			return i;
		}
	}
	return NULL;
}
/*********************************************************************
** Description: This is function that receives a name and age
** of a new instructor to create a new instructor object dynamically and 
** store the object in a vector of pointers to instructor objects if the 
** instructor doesn't already exist.
*********************************************************************/
bool Menu::addInstructor(string name, int age)
{
	if (getInstructor(name) == NULL)
	{
		univ = new Instructor(name, age);
		Instructor* instructor = static_cast<Instructor*>(univ);
		instructors.push_back(instructor);
		return true;
	}
	else
	{
		cout << "The instructor "<< name << " already exists!" << endl;
		return false;
	}
}
/*********************************************************************
** Description: This is function that receives a name, age, rating and 
** grading hours of a new Instructor to create a new instructor object 
** dynamically and store the object in a vector of pointers to instructor 
** objects if the instructor doesn't already exist.
*********************************************************************/
bool Menu::addInstructor(string name, int age, double rating, int gradingHours)
{
	if (getInstructor(name) == NULL)
	{
		univ = new Instructor(name, age, rating, gradingHours);
		Instructor* instructor = static_cast<Instructor*>(univ);
		instructors.push_back(instructor);
		return true;
	}
	else
	{
		cout << "The instructor " << name << " already exists!" << endl;
		return false;
	}
}
/*********************************************************************
** Description: This is function that receives a name of a Instructor
** and if a matching instructor name is found, it then removes that Instructor
** object from the vector of pointers to Instructor objects and then deallocates
** space used for that object.
*********************************************************************/
bool Menu::removeInstructor(string name)
{
	Instructor* instructorToRemove = getInstructor(name);
	if (instructorToRemove != NULL)
	{
		instructors.erase(remove(instructors.begin(), instructors.end(), instructorToRemove), instructors.end());
		delete instructorToRemove;
		return true;
	}
	else
	{
		cout << "The instructor " << name << " could not be found!" << endl;
		return false;
	}
	return true;
}
/*********************************************************************
** Description: This is a function that displays the name, age, rating, and
** grading hours completed of every Instructor stored in the vector of
** pointers to Instructor objects if the vector is not empty.
*********************************************************************/
void Menu::listInstructors()
{
	if (instructors.empty())
	{
		cout << "No Instructors Found: " << endl;
	}
	else
	{
		cout << setw(25) << "Instructor Name:" << setw(5) << "Age:" << setw(8) << "Rating:" << setw(16) << "Grading Hours:" << endl;
		for (auto i : instructors)
		{
			cout << setw(25) << i->getName() << setw(5) << i->getAge() << setw(8) << i->getRating() << setw(8) << i->getGradingHours() << endl;
		}
	}
}
/*********************************************************************
** Description: This is method that receives the name of a Instructor
** and then loops through a vector of pointers to instructor objects to
** find and return a instructor object with a matching name.
*********************************************************************/
Instructor* Menu::getInstructor(string name)
{
	name = toLowercase(name);
	for (auto i : instructors)
	{
		string instructorName = toLowercase(i->getName());
		if (instructorName.find(name) != string::npos)
		{
			return i;
		}
	}
	return NULL;
}

