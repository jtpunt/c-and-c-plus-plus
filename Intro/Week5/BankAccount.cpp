/*********************************************************************
** Author: Jonathan Perry
** Date: 2/8/2017
** Description: This file contains the implementation code of the
** variables and functions needed to maintain a customer's back account.
** This program provides and stores data for the customer's name,
** identification, and current balance by providing features(functions)
** to retrieve their information and make deposits or withdrawels.
*********************************************************************/
#include "BankAccount.hpp"
#include <string>
using namespace std;
/*********************************************************************
** Description: This is a constructor of the BankAccount class which
** takes 3 variables and uses them to initialize the data members.
*********************************************************************/
BankAccount::BankAccount(string name, string id, double balance)
{
	customerName = name;
	customerID = id;
	customerBalance = balance;
}
/*********************************************************************
** Description: This is an accessor function that returns 
** the customer's name.
*********************************************************************/
string BankAccount::getCustomerName()
{
	return customerName;
}
/*********************************************************************
** Description: This is an accessor function that returns
** the customer's ID.
*********************************************************************/
string BankAccount::getCustomerID()
{
	return customerID;
}
/*********************************************************************
** Description: This is an accessor function that returns
** the customer's current balance.
*********************************************************************/
double BankAccount::getCustomerBalance()
{
	return customerBalance;
}
/*********************************************************************
** Description: This is an mutator function that receives a value
** and uses it to decrease the customer's current balance.
*********************************************************************/
void BankAccount::withdraw(double withdrawAmount)
{
		customerBalance -= withdrawAmount;
}
/*********************************************************************
** Description: This is an mutator function that receives a value
** and uses it to increase the customer's current balance.
*********************************************************************/
void BankAccount::deposit(double depositAmount)
{
	customerBalance += depositAmount;
}