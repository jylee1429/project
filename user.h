#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_set>
#include <memory>
#include <vector>
#include <unordered_map>
#include <sqlite3.h>

using namespace std;

// 사용자
class User {
	int userID;						    // 사용자 고유 번호
	string userName;					// 사용자 이름
	string userAddress;					// 사용자 주소
	string userPhoneNumber;				// 사용자 연락처
public:
	// 사용자 고유번호 설정(랜덤 설정, 중복 X)
	// 사용자 이름 설정
	// 사용자 주소 설정
	// 사용자 연락처 설정
};

// 회원
class Member : public User {
	int memberID;						// 회원 ID
	int memberPW;						// 회원 PassWord
	int mileage;						// 회원 마일리지
	int rating;							// 회원 등급   (브론즈/실버/골드/플레티넘)
public:
	// 회원 ID 설정
	// 회원 비밀번호 설정
	// 회원 마일리지 관리
	// 회원 등급 관리
	// 회원 정보 입력
	void setMemberInfo(Member& memberInfo);
};

// 비회원
class Guest : public User {
	int guestPW;						// 비회원 비밀번호
public:
    Guest(string name, string address, int phoneNum, string pw, unordered_set<int>& usedNum)
        : User(name, address, phoneNum), guestPW(pw) {
        userID = "g" + to_string(randomNum(usedNum)); // userID에 'g' + 숫자
    }
	// 비회원 비밀번호 설정
};

// 관리자
class Admin : public User {
	int adminID;						// 관리자 ID
	int adminPW;						// 관리자 비밀번호
public:
	Admin(int id, int pw) : adminID(id), adminPW(pw) {}
	void initDB(void);																				// 데이터 베이스 초기화
	void addProduct(const string& productName, const string& manufacturer, int price, int stock);	// 상품 추가
	void modifyStock(int productID, int newStock);													// 상품 재고 수정
	void deleteProduct(int productID);																// 상품 삭제
	void listProducts() const;     																	// 상품 검색
	// 할인 기간 설정
	// 제품 정보 목록 보기
	// 매출 금액 조회
	// 회원 정보 수정
	void listMember() const;																		// 회원 조회
	void modifyMemberRating(const string& userID, int newRating);									// 회원 rating 수정
	void closeDB();																					// 데이터 베이스 종료
};


// 랜덤 숫자 생성
int randomNum(unordered_set<int>& usedNum) {
    int number;
    do {
        number = rand() % 10000;
    } while (usedNum.find(number) != usedNum.end());
    usedNum.insert(number);
    return number;
}

#endif
