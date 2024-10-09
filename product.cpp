#include "product.h"
#include <iostream>
#include <ctime>

using namespace std;

Product::Product(void) : productName(""), productManufacturer(""), productPrice(0), salePrice(0), productStock(0) { 
	setProductID();
}

string Product::getProductID(void) const {
	return productID;
}

void Product::setProductID(void) {
	// �������� ����

}

int Product::getProductPrice() const {
	return productPrice;
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

void Product::setProductName(string& name) {
	productName = name;
}

string Product::getProductManufacturer(void) const {
	return productManufacturer;
}

void Product::setProductManufacturer(string& manufacturer) {
	productManufacturer = manufacturer;
}

void Product::setDiscount(bool discount) {
	isDiscounted = discount;
}

bool Product::getDiscount(void) {
	return isDiscounted;
}

void Product::setSalePrice(void) {
	// ���αⰣ�� ���
	if (isDiscounted){
		salePrice = static_cast<int>((1.0f - discountRatio) * productPrice);
	}
	// ���αⰣ�� �ƴ� ���
	else {
		salePrice = productPrice;
	}
}

int Product::getSalePrice(void) const {
	return salePrice;
}

// ��¥�� �ٲ� ���� �ش� �Լ� ����
void Product::checkDisCountDay(tm saleStart, tm saleEnd) {
	time_t t = time(nullptr);
	tm currentDate;
	localtime_s(&currentDate, &t);

	// ���� �Ⱓ�� �ش��ϴ� ���
	if (difftime(mktime(&currentDate), mktime(&saleStart)) >= 0 && difftime(mktime(&saleEnd), mktime(&currentDate)) >= 0) {
		setDiscount(true);
	}
	// ���� �Ⱓ�� �ش����� �ʴ� ���
	else {
		setDiscount(false);
	}
}

bool Product::checkProductExist(string id) { 
	// ������ ���̽����� id�� �ش��ϴ� ��ǰ Ȯ��
	// ������� true, ���� ��� false ��ȯ

}

bool Product::registerProduct(string name, string manufacture, int price, int stock) {
	unique_ptr<Product> product(new Product());
	
	product->setProductName(name);
	product->setProductManufacturer(manufacture);
	product->setProductPrice(price);
	product->setProductStock(stock);

	// ��ǰ ���

}

bool Product::deleteProduct(string id) {
	// ������ ���̽����� id�� �ش��ϴ� ��ǰ ����

}

void Product::addProductStock(string id, int cnt) {
	// ������ ���̽����� id�� �ش��ϴ� ��ǰ �ҷ�����
	// ���� ����
	// ������ ���̽��� �ٽ� ����}
}

void Product::subProductStock(string id, int cnt) {
	// ������ ���̽����� id�� �ش��ϴ� ��ǰ �ҷ�����
	// ���� ����
	// ������ ���̽��� �ٽ� ����
}

void Product::setDiscountRatio(float ratio) {
	discountRatio = ratio;
}

float Product::getDiscountRatio(void) {
	return discountRatio;
}