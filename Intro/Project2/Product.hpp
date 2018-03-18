/*********************************************************************
** Author: Jonathan Perry
** Date: 3/15/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for storing and retrieving product 
** data such as the product's ID, title, description, price, and the
** current quantity that's available.
*********************************************************************/
#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product
{
private:
    std::string idCode;
    std::string title;
    std::string description;
    double price;
    int quantityAvailable;
public:
	// Constructor which initializes the product's idCode, title, description, price, and quantity available
    Product(std::string id, std::string t, std::string d, double p, int qa);
	// Returns the product's ID code
    std::string getIdCode();
	// Returns the product's title
    std::string getTitle();
	// Returns the product's description
    std::string getDescription();
	// Returns the product's price
    double getPrice();
	// Returns the product's current quantity available
    int getQuantityAvailable();
	// Decrements the product's quantity available by 1
    void decreaseQuantity();
};

#endif
