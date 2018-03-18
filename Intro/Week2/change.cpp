/*********************************************************************
** Author: Jonathan Perry
** Date: 1/18/17
** Description: This program asks for user input for a (integer) number
** of cents, from 0 to 99, and then outputs a combination of each type
** of coin with the fewest total number of coins used.
*********************************************************************/
#include <iostream>
using namespace std;

int main()
{
	int numOfCents, numOfQuarters, numOfDimes, numOfNickels;
	cout << "Please enter an amount in cents less than a dollar." << endl;
	cin >> numOfCents;

	numOfQuarters = numOfCents / 25; // quarters needed for fewest coins
	numOfCents %= 25; // calculating what cent value remains after subtractring quarter cent value
	numOfDimes = numOfCents / 10; // dimes needed for fewest coins
	numOfCents %= 10; // calculating what cent value remains after subtracting dime cent value
	numOfNickels = numOfCents / 5; // nickels needed for fewest coins
	numOfCents %= 5; // calculating what cent value remains after subtracting nickel cent value
	//cent value left in numOfCents is the penny amount

	cout << "Your change will be:" << endl;
	cout << "Q: " << numOfQuarters << endl;
	cout << "D: " << numOfDimes << endl;
	cout << "N: " << numOfNickels << endl;
	cout << "P: " << numOfCents << endl;
}