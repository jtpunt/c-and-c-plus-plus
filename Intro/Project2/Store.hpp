/*********************************************************************
** Author: Jonathan Perry
** Date: 3/15/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for storing and retreiving pointers 
** to each individual customer and product, searching for a product,
** adding a product to a customer's cart, and checking out.
*********************************************************************/
#ifndef STORE_HPP
#define STORE_HPP

#include <string>
#include "Customer.hpp"

class Store
{
private:
	// Vector containing pointers to Product objects
    std::vector<Product*> inventory;
	// Vector containing pointers to Customer objects
    std::vector<Customer*> members;
public:
	// Adds a pointer to a Product to the vector inventory
    void addProduct(Product* p);
	// Adds a pointer to a Customer to vector members
    void addMember(Customer* c);
	// Returns pointer to Product with matching ID.
    Product* getProductFromID(std::string);
	// Returns pointer to Customer with matching ID.
    Customer* getMemberFromID(std::string);
	// Searches for a Product with a matching title or description
    void productSearch(std::string str);
	/* Adds a valid product to a valid customer's cart
	   if the quantity available is greater than zero*/
    void addProductToMemberCart(std::string pID, std::string mID);
	/* Prints out each title and price of the product(s)
	   retrieved from the customer's cart and then prints out the 
	   subtotal, shipping cost, and total cost before emptying their cart.*/
    void checkOutMember(std::string mID);
};

#endif
