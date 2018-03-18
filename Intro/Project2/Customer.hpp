/*********************************************************************
** Author: Jonathan Perry
** Date: 3/15/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for storing customer data such
** as their name, account ID number, whether or not they're a 
** premium member of the store, and what products they currently have 
** in their cart for making a purchase.
*********************************************************************/
#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <vector>
#include "Product.hpp"

class Customer
{
private:
   std::vector<std::string> cart;
   std::string name;
   std::string accountID;
   bool premiumMember;
public:
   // Constructor which initializes the Customer's name, account ID, and premium member status
   Customer(std::string n, std::string a, bool pm);
   // Returns the account ID of the customer
   std::string getAccountID();
   // Returns the product ID(s) in the customer's cart 
   std::vector<std::string> getCart();
   // Adds the Product ID code to the customer's cart
   void addProductToCart(std::string);
   // Returns whether the customer is a premium member
   bool isPremiumMember();
   // Removes all products from the customer's cart
   void emptyCart();
};

#endif
