#ifndef _ORDER_H_
#define _ORDER_H_

#include <map>
#include <sstream>
#include "product.h"
#include "user.h"

class Order {	
	map<string, int> orderList;								// �ֹ��� ��ǰ ���(��ǰ ID, �ֹ� ����)
	int totalPrice;											// �� �ֹ� �ݾ�
	string orderAddress;									// ����� �ּ�
	string orderState;										// �ֹ� ����
	bool isMember;											// ȸ�� / ��ȸ�� ����
protected:
	string orderID;											// �ֹ���ȣ
public:
	Order(void);											// ������
	virtual void transmitOrder(void) = 0;					// server�� �ֹ� ��û
	virtual void handleOrder(void) = 0;						// server���� �ֹ� ó��
	void setOrderState(string& state);						// ��� ���� ����
	string getOrderState(void) const;						// ��� ���� ���
	virtual void setOrderID(void) = 0;						// �ֹ� ��ȣ ����
	string getOrderID(void) const;							// �ֹ� ��ȣ ���
	void addTotalPrice(int price);							// �� �ֹ� �ݾ׿��� �ݾ� �߰�
	void subTotalPrice(int price);							// �� �ֹ� �ݾ׿��� �ݾ� ����
	int getTotalPrice(void) const;							// �� �ֹ� �ݾ� ���
	void setOrderAddress(string& address);					// ��� �ּ� ����
	string getOrderAddress(void) const;						// ��� �ּ� ���
	virtual bool checkMileageUsed(void) = 0;				// ���ϸ��� ��� ����
	void addQuantity(Product& product, int orderQuantity);	// ��ٱ��Ͽ� ���� �߰�
	void subQuantity(Product& product);						// ��ٱ��Ͽ� ���� ����
	void makeRandomNumber(stringstream& id);				// orderID�� ���� ���� ���� ����
	virtual ~Order(void) = default;							// �Ҹ���
};

// ȸ�� �ֹ�
class OrderMember : public Order {
	Member orderMember;										// �ֹ��� ȸ�� ����
	bool isMileageUsed;										// ���ϸ��� ��� ����
public:
	OrderMember();											// ������
	void setMemInfo(Member& member);						// �ֹ��� ȸ�� ���� ����
	Member getMemInfo(void) const;							// �ֹ��� ȸ�� ���� ���
	void transmitOrder(void) override;								
	void handleOrder(void) override;		
	void setOrderID(void) override;
	bool getMileageUsed(void) const;						// ���ϸ��� ��뿩�� ���(���ϸ��� ��� �� ���� X)
	void setMileageUsed(bool option);						// ���ϸ��� ��뿩�� ����
	~OrderMember(void) = default;
};

// ��ȸ�� �ֹ�
class OrderGuest : public Order {
	Guest orderGuest;										// �ֹ��� ��ȸ�� ����
public:
	OrderGuest();
	void setMemInfo(Guest& guest);							// �ֹ��� ��ȸ�� ���� ����	
	Guest getMemInfo(void) const;							// �ֹ��� ��ȸ�� ���� ���
	void transmitOrder(void) override;
	void handleOrder(void) override;
	void setOrderID(void) override;
	~OrderGuest(void) = default;
};

#endif