/********************************************************
** Author: Jonathan Perry
** Date: 1/10/17	
** Description: This is the week 1 assignment for CS161.
** 	The program asks for user input and then displays
**	that value as output.
********************************************************/

#include <iostream>
#include <string>

// a simple example program
int main()
{
	std::string faveAnimal;
	std::cout << "Please enter your favorite animal." << std::endl;
	std::cin >> faveAnimal;
	std::cout << "Your favorite animal is the " << faveAnimal;
	std::cout << "." << std::endl;

	return 0;
}	
