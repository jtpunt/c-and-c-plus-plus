/*********************************************************************
** Author: Jonathan Perry
** Date: 4/30/2017
** Description: This header file defines the class specifications of
** variables and functions needed for creating and managing an information
** system for a university by adding and deleting students, instructors,
** and buildings in real time.
*********************************************************************/
#ifndef MENU_HPP
#define MENU_HPP
#include <vector>
#include "Student.hpp"
#include "Instructor.hpp"
#include "Buildings.hpp"
#include "University.hpp"
class Menu
{
private:
	std::vector <Student*> students;
	std::vector <Instructor*> instructors;
	std::vector <Buildings*> buildings;
	std::vector <University*> universities;
	// Create base pointer to the University Object
	University* univ;
public:
	Menu();
	void correctInput();
	void displayMenu();

	bool addUniversity(std::string);
	bool removeUniversity(std::string);
	void listUniversities();
	University* getUniversity(std::string);

	bool addBuilding(std::string, int, std::string);
	bool removeBuilding(std::string);
	void listBuildings();
	Buildings* getBuilding(std::string);


	bool addStudent(std::string, int);
	bool addStudent(std::string, int, double, int);
	bool removeStudent(std::string);
	void listStudents();
	Student* getStudent(std::string);

	bool addInstructor(std::string, int);
	bool addInstructor(std::string, int, double, int);
	bool removeInstructor(std::string);
	void listInstructors();
	Instructor* getInstructor(std::string);

};
#endif // !#MENU_HPP
#pragma once
