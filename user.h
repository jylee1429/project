#ifndef _USER_H_
#define _USER_H_

#include <string>

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
	int rating;							// 회원 등급
public:
	// 회원 ID 설정
	// 회원 비밀번호 설정
	// 회원 마일리지 관리
	// 회원 등급 관리
};

// 비회원
class Guest : public User {
	int guestPW;						// 비회원 비밀번호
public:
	// 비회원 비밀번호 설정
};

// 관리자
class Admin : public User {
	int adminID;						// 관리자 ID
	int adminPW;						// 관리자 비밀번호
public:
	// 상품 추가
	// 상품 입고
	// 상품 삭제
	// 상품 검색
	// 할인 기간 설정
	// 제품 정보 목록 보기
	// 매출 금액 조회
	// 회원 정보 수정
};

// 회원 가입
// 로그인
// 비회원 설정


#endif
