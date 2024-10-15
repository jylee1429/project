#ifndef _ORDER_H_
#define _ORDER_H_

#include <map>
#include <sstream>
#include "product.h"
#include "user.h"

class Order {	
	map<string, int> orderList;								// 주문한 제품 목록(상품 ID, 주문 개수)
	int totalPrice;											// 총 주문 금액
	string orderAddress;									// 배송할 주소
	string orderState;										// 주문 상태
	bool isMember;											// 회원 / 비회원 여부
protected:
	string orderID;											// 주문번호
public:
	Order(void);											// 생성자
	virtual void transmitOrder(void) = 0;					// server로 주문 신청
	virtual void handleOrder(void) = 0;						// server에서 주문 처리
	void setOrderState(string& state);						// 배송 상태 설정
	string getOrderState(void) const;						// 배송 상태 출력
	virtual void setOrderID(void) = 0;						// 주문 번호 설정
	string getOrderID(void) const;							// 주문 번호 출력
	void addTotalPrice(int price);							// 총 주문 금액에서 금액 추가
	void subTotalPrice(int price);							// 총 주문 금액에서 금액 차감
	int getTotalPrice(void) const;							// 총 주문 금액 출력
	void setOrderAddress(string& address);					// 배송 주소 설정
	string getOrderAddress(void) const;						// 배송 주소 출력
	virtual bool checkMileageUsed(void) = 0;				// 마일리지 사용 여부
	void addQuantity(Product& product, int orderQuantity);	// 장바구니에 물건 추가
	void subQuantity(Product& product);						// 장바구니에 물건 제거
	void makeRandomNumber(stringstream& id);				// orderID에 넣을 랜덤 숫자 생성
	virtual ~Order(void) = default;							// 소멸자
};

// 회원 주문
class OrderMember : public Order {
	Member orderMember;										// 주문한 회원 정보
	bool isMileageUsed;										// 마일리지 사용 여부
public:
	OrderMember();											// 생성자
	void setMemInfo(Member& member);						// 주문한 회원 정보 설정
	Member getMemInfo(void) const;							// 주문한 회원 정보 출력
	void transmitOrder(void) override;								
	void handleOrder(void) override;		
	void setOrderID(void) override;
	bool getMileageUsed(void) const;						// 마일리지 사용여부 출력(마일리지 사용 시 매출 X)
	void setMileageUsed(bool option);						// 마일리지 사용여부 설정
};

// 비회원 주문
class OrderGuest : public Order {
	Guest orderGuest;										// 주문한 비회원 정보
public:
	OrderGuest();
	void setMemInfo(Guest& guest);							// 주문한 비회원 정보 설정	
	Guest getMemInfo(void) const;							// 주문한 비회원 정보 출력
	void transmitOrder(void) override;
	void handleOrder(void) override;
	void setOrderID(void) override;
};

#endif