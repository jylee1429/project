#include "order.h"
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <sstream>
#include <iomanip> 

Order::Order(void) : orderID(""), totalPrice(0), orderAddress(""), orderState(""), isMember(false), orderList() {

}

void Order::setOrderState(string& state) {
	orderState = state;
}

string Order::getOrderState(void) const {
	return orderState;
}

string Order::getOrderID(void) const {
	return orderID;
}

void Order::addTotalPrice(int price) {
	totalPrice += price;
}

void Order::subTotalPrice(int price) {
	totalPrice -= price;
}

int Order::getTotalPrice(void) const {
	return totalPrice;
}

void Order::setOrderAddress(string& address) {
	orderAddress = address;
}

string Order::getOrderAddress(void) const {
	return orderAddress;
}

void Order::addQuantity(Product& product, int orderQuantity) {
	string productID = product.getProductID();
	int currentStock = product.getProductStock();
	int actualAddCount = 0;

	// 장바구니에 있는 물건인 경우 cnt만큼 개수 증가
	if (orderList.find(product.getProductID()) != orderList.end()) {
		orderList[productID] += orderQuantity;
		// 주문하려는 수량이 재고를 넘지 않도록 조정
		if (orderList[productID] > currentStock) {
			// 실제로 추가된 수량
			actualAddCount = orderList[productID] - currentStock;
			orderList[productID] = currentStock;
		}
	}
	// 장바구니에 없는 물건인 경우
	else {
		// 주문하려는 수량이 재고를 넘지 않도록 조정
		if (orderQuantity > currentStock) {
			orderQuantity = currentStock;
		}
		// 실제로 추가된 수량
		actualAddCount = orderQuantity;
		orderList.insert(make_pair(product.getProductID(), orderQuantity));
	}

	addTotalPrice(product.getProductPrice() * actualAddCount);
}

void Order::subQuantity(Product& product) {
	string productID = product.getProductID();
	int orderQuantity = orderList[productID];

	orderList.erase(productID);
	subTotalPrice(product.getProductPrice() * orderQuantity);
}


void Order::makeRandomNumber(stringstream& id) {
	random_device rd;

	// 고유한 시간 값 추가
	time_t t = time(nullptr);
	id << t;
	// 중복 방지를 위한 랜덤한 숫자 추가
	mt19937 gen(rd());									// random라이브러리에서 제공하는 난수 생성 엔진
	uniform_int_distribution<int> dis(0, 9999);			// 범위 설정
	int randomNum = dis(gen);							// 난수 생성
	id << setfill('0') << setw(4) << randomNum;			// 난수를 4자리로 고정;
}

OrderMember::OrderMember() : Order(), orderMember(/* 초기화 인자 */), isMileageUsed(false) {
	// orderID 생성
	setOrderID();
}

void OrderMember::setMemInfo(Member& member) {
	orderMember = member;
}

Member OrderMember::getMemInfo(void) const {
	return orderMember;
}

void OrderMember::transmitOrder(void) {
	// TCP 통신을 기반으로 client에서 server로 전송
	// Order객체를 전송
}

void OrderMember::handleOrder(void) {
	// server에서 client에게 받은 Order객체를 받음
	// 받은 order객체를 데이터베이스에 저장
	// 마일리지 사용여부 확인
	// 주문 진행 상황 확인해서 처리
}

void OrderMember::setOrderID(void) {
	stringstream id;

	// 회원의 경우 주문번호 맨 앞에 M을 추가
	id << 'M';
	makeRandomNumber(id);

	orderID =  id.str();								
}

bool OrderMember::getMileageUsed(void) const {
	return isMileageUsed;
}

void OrderMember::setMileageUsed(bool option) {
	isMileageUsed = option;
}

OrderGuest::OrderGuest() : Order(), orderGuest(/* 초기화 인자 */) {
	// orderID 생성
	setOrderID();
}

void OrderGuest::setMemInfo(Guest& guest) {
	orderGuest = guest;
}

Guest OrderGuest::getMemInfo(void) const {
	return orderGuest;
}

void OrderGuest::transmitOrder(void) {

}

void OrderGuest::handleOrder(void) {

}

void OrderGuest::setOrderID(void) {
	stringstream id;

	// 비회원의 경우 주문번호 맨 앞에 G을 추가
	id << 'G';
	makeRandomNumber(id);

	orderID = id.str();
}