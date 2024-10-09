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

	// ��ٱ��Ͽ� �ִ� ������ ��� cnt��ŭ ���� ����
	if (orderList.find(product.getProductID()) != orderList.end()) {
		orderList[productID] += orderQuantity;
		// �ֹ��Ϸ��� ������ ��� ���� �ʵ��� ����
		if (orderList[productID] > currentStock) {
			// ������ �߰��� ����
			actualAddCount = orderList[productID] - currentStock;
			orderList[productID] = currentStock;
		}
	}
	// ��ٱ��Ͽ� ���� ������ ���
	else {
		// �ֹ��Ϸ��� ������ ��� ���� �ʵ��� ����
		if (orderQuantity > currentStock) {
			orderQuantity = currentStock;
		}
		// ������ �߰��� ����
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

	// ������ �ð� �� �߰�
	time_t t = time(nullptr);
	id << t;
	// �ߺ� ������ ���� ������ ���� �߰�
	mt19937 gen(rd());									// random���̺귯������ �����ϴ� ���� ���� ����
	uniform_int_distribution<int> dis(0, 9999);			// ���� ����
	int randomNum = dis(gen);							// ���� ����
	id << setfill('0') << setw(4) << randomNum;			// ������ 4�ڸ��� ����;
}

OrderMember::OrderMember() : Order(), orderMember(/* �ʱ�ȭ ���� */), isMileageUsed(false) {
	// orderID ����
	setOrderID();
}

void OrderMember::setMemInfo(Member& member) {
	orderMember = member;
}

Member OrderMember::getMemInfo(void) const {
	return orderMember;
}

void OrderMember::transmitOrder(void) {
	// TCP ����� ������� client���� server�� ����
	// Order��ü�� ����
}

void OrderMember::handleOrder(void) {
	// server���� client���� ���� Order��ü�� ����
	// ���� order��ü�� �����ͺ��̽��� ����
	// ���ϸ��� ��뿩�� Ȯ��
	// �ֹ� ���� ��Ȳ Ȯ���ؼ� ó��
}

void OrderMember::setOrderID(void) {
	stringstream id;

	// ȸ���� ��� �ֹ���ȣ �� �տ� M�� �߰�
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

OrderGuest::OrderGuest() : Order(), orderGuest(/* �ʱ�ȭ ���� */) {
	// orderID ����
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

	// ��ȸ���� ��� �ֹ���ȣ �� �տ� G�� �߰�
	id << 'G';
	makeRandomNumber(id);

	orderID = id.str();
}