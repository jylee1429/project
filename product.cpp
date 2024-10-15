#include "product.h"
#include <iostream>
#include <ctime>

using namespace std;

Product::Product(string name="", string manufacture="", int price = 0, int stock = 0) {
	productID = "";
	productName = name;
	productManufacturer = manufacture;
	productPrice = price;
	discountPrice = price;
	productStock = stock;
	isDiscounted = false;
}

string Product::getProductID(void) const {
	return productID;
}

void Product::setProductID(void) {
	
}

int Product::getProductPrice() const {

	if (isDiscounted) {
		return discountPrice;
	}

	else {
		return productPrice;
	}
}

void Product::setProductPrice(int price) {
	productPrice = price;
}

int Product::getProductStock(void) const {
	return productStock;
}

void Product::setProductStock(int stock) {
	productStock = stock;
}

string Product::getProductName(void) const {
	return productName;
}

void Product::setProductName(string name) {
	productName = name;
}

string Product::getProductManufacturer(void) const {
	return productManufacturer;
}

void Product::setProductManufacturer(string manufacturer) {
	productManufacturer = manufacturer;
}

void Product::setDiscount(bool discount) {
	isDiscounted = discount;
}

bool Product::getDiscount(void) const {
	return isDiscounted;
}

void Product::changeProductPrice(tm saleStart, tm saleEnd) {
	time_t t = time(nullptr);
	tm* currentDate = localtime(&t);

	if (difftime(mktime(currentDate), mktime(&saleStart)) >= 0 && difftime(mktime(&saleEnd), mktime(currentDate)) >= 0) {
		isDiscounted = true;
	}
	else {
		isDiscounted = false;
	}
}

void Product::setDiscountPrice(float ratio) {
	discountPrice = productPrice * (1 - ratio);
}

bool Product::checkProductExist(string id) { 

}

bool Product::registerProduct(string name, string manufacture, int price, int stock) {



}

bool Product::deleteProduct(string id) {

}

void Product::addProductStock(string id, int cnt) {

}

void Product::subProductStock(string id, int cnt) {

}

