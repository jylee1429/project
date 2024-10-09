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
	// 랜덤으로 생성

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
	// 할인기간인 경우
	if (isDiscounted){
		salePrice = static_cast<int>((1.0f - discountRatio) * productPrice);
	}
	// 할인기간이 아닌 경우
	else {
		salePrice = productPrice;
	}
}

int Product::getSalePrice(void) const {
	return salePrice;
}

// 날짜가 바뀔때 마다 해당 함수 실행
void Product::checkDisCountDay(tm saleStart, tm saleEnd) {
	time_t t = time(nullptr);
	tm currentDate;
	localtime_s(&currentDate, &t);

	// 세일 기간에 해당하는 경우
	if (difftime(mktime(&currentDate), mktime(&saleStart)) >= 0 && difftime(mktime(&saleEnd), mktime(&currentDate)) >= 0) {
		setDiscount(true);
	}
	// 세일 기간에 해당하지 않는 경우
	else {
		setDiscount(false);
	}
}

bool Product::checkProductExist(string id) { 
	// 데이터 베이스에서 id에 해당하는 제품 확인
	// 있을경우 true, 없을 경우 false 반환

}

bool Product::registerProduct(string name, string manufacture, int price, int stock) {
	unique_ptr<Product> product(new Product());
	
	product->setProductName(name);
	product->setProductManufacturer(manufacture);
	product->setProductPrice(price);
	product->setProductStock(stock);

	// 상품 등록

}

bool Product::deleteProduct(string id) {
	// 데이터 베이스에서 id에 해당하는 상품 삭제

}

void Product::addProductStock(string id, int cnt) {
	// 데이터 베이스에서 id에 해당하는 상품 불러오기
	// 개수 변경
	// 데이터 베이스에 다시 저장}
}

void Product::subProductStock(string id, int cnt) {
	// 데이터 베이스에서 id에 해당하는 상품 불러오기
	// 개수 변경
	// 데이터 베이스에 다시 저장
}

void Product::setDiscountRatio(float ratio) {
	discountRatio = ratio;
}

float Product::getDiscountRatio(void) {
	return discountRatio;
}