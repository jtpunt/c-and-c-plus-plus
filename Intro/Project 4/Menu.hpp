/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This header file defines the class specifications of
** variables and functions needed for creating a visual menu for the 
** user to navigate through the program.
*********************************************************************/
#ifndef MENU_HPP
#define MENU_HPP
#include <string>
#include <vector>
class Menu
{
private:
	// Created for easy display of creature descriptions
	std::string creatureType[5][5] = { {"Vampire", "1d12", "1d6*charm", "1", "18" },
										{"Barbarian", "2d6", "2d6", "0", "12" },
										{"Blue Men", "2d10", "3d6", "3", "12*Mob" },
										{"Medusa", "2d6*Glare", "1d6", "3", "8" },
										{"Harry Potter", "2D6", "0", "1", "10/20*HogWarts" },};
	std::vector <int> team1; // Stores the input for creatures wanted on team 1
	std::vector <int> team2; // Stores the input for creatures wanted on team 2
public:
	// Constructor which calls displayMenu function
	Menu();
	void clearInput();
	void displayMenu();
	void displayMenu1();
	void displayCreatures();
	void displayDescriptions();
	void getCreatures();
	void inputCreatures(int);
	// CHANGES
	//bool validateCreature(std::string);
	void playGame();
};

#endif
