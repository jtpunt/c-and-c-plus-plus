/*********************************************************************
** Author: Jonathan Perry
** Date: 5/1/2017
** Description: This header file defines the class specifications of
** the variables and functions needed for creating grocery
** list item's such as the item's name, unit type, unit price, and the
** specified quantity to buy.
*********************************************************************/
#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>
class Item
{
private:
    std::string name;
    std::string unit; // i.e. can box, pound, ounce
    double unitPrice;
    int quantityToBuy;
public:
	// Constructor which initializes the item's name, unit type, price, and the quantity to buy
	Item(std::string, std::string , double, int);

	// Sets the item's name
	void setName(const std::string);
	// Returns the item's name
    std::string getName() const;

	// Sets the item's unit
	void setUnit(const std::string);
	// Returns the item's unit
    std::string getUnit() const;

	// Sets the item's price
	void setUnitPrice(const double);
	// Returns the item's price
    double getUnitPrice() const;

	// Sets the quantity amount to buy
	void setQuantityToBuy(const int);
	// Returns the quantity amount to buy
    int getQuantityToBuy() const;

	// Returns the item's price times the quantity amount to buy
	double getExtendedPrice() const;
};

#endif
