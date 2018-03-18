/*********************************************************************
** Author: Jonathan Perry
** Date: 2/1/2017
** Description: This header file defines the class specifications of the
** variables and functions needed to maintain a customer's back account.
** This program provides and stores data for the customer's name,
** identification, and current balance by providing features(functions)
** to retrieve their information and make deposits or withdrawels.
*********************************************************************/
#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP
#include <string>
using namespace std;
class BankAccount
{
private:
	string customerName; // Name of the customer
	string customerID; // ID of the customer
	double customerBalance; // Balance of the customer
public:
	// Constructor that takes the customer's name, ID, and balance to initialize the data members
	BankAccount(string, string, double);

	// getter prototypes
	string getCustomerName(); // Retrieves the customer's name
	string getCustomerID(); // Retrieves the customer's ID
	double getCustomerBalance(); // Retrieves the customer's current balance
	// setter prototypes
	void withdraw(double); // This prototype function decreases the customer's balance
	void deposit(double); // This prototype function increases the customer's balance
};
#endif