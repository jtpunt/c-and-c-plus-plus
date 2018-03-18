#include "Store.hpp"
#include <iostream>
using namespace std;

int main()
{
	Store store1;
	store1.addProduct(new Product("LG 29'", "LG Ultrawide Monitor", "29' Ultrawide Gaming Monitor", 199.99, 2));
	store1.addProduct(new Product("LG Speaker", "LG Speaker System", "LG 2.1 Bluetooth Speaker System", 199.99, 0));
	store1.addProduct(new Product("EVGA 770", "EVGA GTX 770", "EVGA gtx 770 Superclocked", 299.99, 1));
	store1.addProduct(new Product("TI-89 plus", "TI-89 plus", "Texas Instruments TI-83 Plus", 99.99, 3));
	store1.addMember(new Customer("Jonathan", "123", true));
	store1.addMember(new Customer("Taylor", "321", false));
	store1.productSearch("texas instruments");
	store1.addProductToMemberCart("LG 29'", "321");
	store1.addProductToMemberCart("LG 29'", "321");
	store1.addProductToMemberCart("LG 29'", "321");
	store1.addProductToMemberCart("EVGA 770", "321");
	store1.addProductToMemberCart("EVGA 770", "321");
	store1.addProductToMemberCart("EVGA 770", "123");
	store1.addProductToMemberCart("LG Speaker", "123");
	store1.checkOutMember("321");
	cout << "\n";
	store1.checkOutMember("123");
}