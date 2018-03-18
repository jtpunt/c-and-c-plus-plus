/*********************************************************************
** Author: Jonathan Perry
** Date: 1/25/2017
** Description: This program prompts the user for an integer that the
** player will try to guess. The players enters their guess each time
** with the program notifying them that their guess is too high or too 
** low until they have guessed correctly and then tells them how many
** guesses it took them.
*********************************************************************/
#include <iostream>
using namespace std;

int main()
{
	int numberGuess, // The number for the player to guess
		playerGuess = 0, // The number the player guesses
		guessCounter = 0; // The counter for the amount of guesses it took

	// Ask the number to be guessed and store it in numberGuess
	cout << "Enter the number for the player to guess." << endl;
	cin >> numberGuess;
	// Ask for the player to enter their guess
	cout << "Enter your guess." << endl;
	// Keep looping until they guess the correct number
	while(numberGuess != playerGuess)
	{
		cin >> playerGuess; // Read the player's next guess
		if (playerGuess > numberGuess) // See if the guess is too high
		{
			cout << "Too high - try again." << endl;
			guessCounter++; // increment guess attempt
		}
		else if (playerGuess < numberGuess) // See if the guess is too low
		{
			cout << "Too low - try again" << endl;
			guessCounter++; // increment guess attempt
		}
		else // Player guessed correctly when above if statements fail
		{
			guessCounter++; // increment last guess attempt
		}
	}
	cout << "You guessed it in " << guessCounter << " tries." << endl;
}