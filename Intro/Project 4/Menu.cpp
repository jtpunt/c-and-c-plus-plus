/*********************************************************************
** Author: Jonathan Perry
** Date: 5/15/2017
** Description: This file contains the implementation code of the 
** variables and functions needed for creating a visual menu for the
** user to navigate through the program.
*********************************************************************/
#include "Menu.hpp"
#include "PlayGame.hpp"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::setw;
using std::string;
/*********************************************************************
** Description: This is a constructor of the Menu class which creates
** the List object and then displays the main menu to the user.
*********************************************************************/
Menu::Menu()
{
	displayMenu();
}
/*********************************************************************
** Description: This is a function that resets any error flags for cin
** and discards up to 1,000 characters from the input buffer.
*********************************************************************/
void Menu::clearInput()
{
	cin.clear();
	// Discards up to 1,000 characters from the input buffer or until a newline is read
	cin.ignore(1000, '\n');
}
/*********************************************************************
** Description: This is a function that receives a string and converts
** and returns that string in lowercase characters.
*********************************************************************/
string toLowerCase(string str)
{
	for (int i = 0; str[i]; i++)
	{
		// converts search word to lowercase
		str[i] = tolower(str[i]);
	}
	return str;
}
/*********************************************************************
** Description: This is a function that displays the menu to the user
** so that they may navigate through different features of the program.
*********************************************************************/
void Menu::displayMenu()
{
	int menuChoice = 0;

	cout << "\n____________________________________________________________" << endl;
	cout << "|                       MENU                               |" << endl;
	cout << "|1. Build a team of creatures to fight each other:         |" << endl;
	cout << "|2. See who wins:                                          |" << endl;
	cout << "|3. Exit                                                   |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		displayMenu1();
		break;
	case 2:
		playGame();
		displayMenu1();
		break;
	case 3:
		exit(0);
		break;
	default:
		cout << "Invalid input entered, please try again: " << endl;
		displayMenu();
		break;
	}
}
/*********************************************************************
** Description: This is a function that displays the Creature menu to the user
** so that they may view and choose two creatures to fight.
*********************************************************************/
void Menu::displayMenu1()
{
	int menuChoice = 0;
	string creatureName;
	cout << "____________________________________________________________" << endl;
	cout << "|                       MENU - CREATURES                   |" << endl;
	cout << "|1. Display All Creatures and Their Stats                  |" << endl;
	cout << "|2. Display Creature Descriptions and Special Abilities    |" << endl;
	cout << "|3. Enter Creature Names to Battle it Out!                 |" << endl;
	cout << "|4. Return to Main Menu                                    |" << endl;
	cout << "|__________________________________________________________|" << endl;
	cout << " Enter a number from above to get started: ";
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		displayCreatures();
		displayMenu1();
		break;
	case 2:
		displayDescriptions();
		break;
	case 3:
		//
		getCreatures();
		break;
	case 4:
		displayMenu();
		break;
	default:
		cout << "Invalid input entered, please try again: " << endl;
		displayMenu1();
		break;
	}
}
/*********************************************************************
** Description: This is a function that prints every creature type, and
** their attack/defense/armor/strength specifications.
*********************************************************************/
void Menu::displayCreatures()
{
	cout << setw(16) << "Type" << setw(16) << "Attack" << setw(16) << "Defense";
	cout << setw(16) << "Armor" << setw(16) << "Strength" << endl;
	for (auto& row : creatureType)
	{
		for (auto& columns : row)
		{
			cout << setw(16) << columns;
		}
		cout << endl;
	}
}
/*********************************************************************
** Description: This is a function that prints every creature's description
** and special ability.
*********************************************************************/
void Menu::displayDescriptions()
{
	cout << "Creature Descriptions:" << endl;
	cout << setw(21) << "Creature Name" << "   Descriptions" << endl;
	cout << setw(21) << "Vampire:" << "   Suave, debonair, but vicious and surprisingly resilient!" << endl;
	cout << setw(21) << "Vampire Abilities:" << "   *Charm*: Vampires can charm an opponent into not attacking.";
	cout << setw(21) << "\n\t\t\tFor a given attack there is a 50 % chance that their opponent does not actually attack them." << endl;
	cout << setw(21) << "Barbarian:" << "   Think Conan or Hercules from the movies.Big sword, big muscles, bare torso." << endl;
	cout << setw(21) << "Blue Men:" << "   They are small(6\" tall), fast and tough. So they are hard to hit and can take some damage.";
	cout << setw(21) << "\n\t\t\tAs for the attack value, you can do a LOT of damage when you can crawl inside the armor or clothing of your opponent." << endl;
	cout << setw(21) << "Blue Men Abilities:" << "  *Mob* - The Blue Men are actually a swarm of small individuals. For every 4 points of damage(round down),";
	cout << setw(21) << "\n\t\t\tthey lose one defense die. For example, when they reach strength of 8 they only have 2d6 for defense." << endl;
	cout << setw(21) << "Medusa:" << "   Scrawny lady with snakes for hair.They help with fighting. Just don\'t look at her!" << endl;
	cout << setw(21) << "Medusa Abilities:" << "   *Glare* - If a Medusa rolls a 12 in attack, then the target has looked her in the eyes and is turned to stone.";
	cout << setw(21) << "\n\t\t\tThe Medusa wins! If Medusa uses Glare on Harry Potter on his first life, then Harry Potter get back to life.";
	cout << setw(21) << "\n\t\t\tIf the Vampire's Charm ability activates versus Medusa's Glare, the Vampire's Charm trump the Glare." << endl;
	cout << setw(21) << "Harry Potter:" << "   Why are you reading this ? How can you not know who Harry Potter is ?" << endl;
	cout << setw(21) << "Potter\'s Abillities:" << "   *Hogwarts* - If Harry dies(i.e.strength <= 0), he immediately recovers and his total strength becomes 20. If he were to die again, then he\'s dead." << endl;
	displayMenu1();
}
/*********************************************************************
** Description: This is a function that prompts the user to enter in
** two creature names so that they both can fight each other.
*********************************************************************/
void Menu::getCreatures()
{
	string creature1;
	string creature2;
	int num_of_creatures;

	// Has the user already added creatures?
	if (!team1.empty() || !team2.empty())
	{
		cout << "There are creatures already selected to fight. Returning to Menu." << endl;
		displayMenu();
	}
	//**CHANGED
	cout << "How many creatures do you want on each teams?" << endl;
	cout << "Please enter a number from 1 to 20: ";
	cin >> num_of_creatures;
	while (!cin || num_of_creatures < 0 || num_of_creatures > 20)
	{
		clearInput();
		cout << "Please enter a number from 1 to 20: ";
		cin >> num_of_creatures;
	}
	inputCreatures(num_of_creatures);
	displayMenu1();
}
void Menu::inputCreatures(int num_of_creatures)
{
	int creature_Choice = 0;
	string displayInstructions = "Please enter one of the numbers below to\n";
	displayInstructions += "1 for Vampire \n";
	displayInstructions += "2 for Barbarian\n";
	displayInstructions += "3 for Blue Men\n";
	displayInstructions += "4 for Medusa\n";
	displayInstructions += "5 for Harry Potter\n";
	for (int i = 0; i < num_of_creatures; i++)
	{
		cout << displayInstructions;
		cout << "\nEnter Team 1 Creature Number " << i + 1 << ": ";
		cin >> creature_Choice;

		// Send their input to validateCreature to make sure they entered a creature's name
		while (!cin || creature_Choice < 0 || creature_Choice > 5)
		{
			clearInput();
			cout << "\nEnter Team 1 Creature Number " << i + 1 << ": ";
			cin >> creature_Choice;
		} 
		team1.push_back(creature_Choice);

		cout << "\nEnter Team 2 Creature Number " << i + 1 << ": ";
		cin >> creature_Choice;

		// Send their input to validateCreature to make sure they entered a creature's name
		while (!cin || creature_Choice < 0 || creature_Choice > 5)
		{
			clearInput();
			cout << displayInstructions;
			cout << "\nEnter Team 2 Creature Number " << i + 1 << ": ";
			cin >> creature_Choice;
		}
		team2.push_back(creature_Choice);
	}
}
/*********************************************************************
** Description: This is a function that receives the name of the creature
** and compares it every name within the array that holds creature
** information to find a match.
*********************************************************************/
void Menu::playGame()
{
	// See if input has been gathered on creatures selected to fight on both teams
	if (team1.empty() || team2.empty())
	{
		cout << "No creatures have been selected, returning to main menu." << endl;
		displayMenu();
	}
	// Start the game and send the vector of creatures selected by both teams
	PlayGame(team1, team2);
	//
	// Reset the team's vector in case another game is played
	team1.clear();
	team2.clear();
}