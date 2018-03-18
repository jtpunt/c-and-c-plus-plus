/*********************************************************************
** Author: Jonathan Perry
** Date: 1/18/2017
** Description: This program asks for user input on a temperature in
** in Celcius, and then outputs that temperature in Fahrenheit.
*********************************************************************/
#include <iostream>

using namespace std;

int main()
{
	double  celcius, convToFahrenheit;
	cout << "Please enter a Celcius temperature." << endl;
	cin >> celcius; // reads user input into celcius variable

	convToFahrenheit = ((celcius * 9.0) / 5.0) + 32; // Formula which converts Celcius to Fahrenheit

	cout << "The equivalent Fahrenheit temperature is:\n" << convToFahrenheit << endl;
}