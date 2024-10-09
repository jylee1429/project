#ifndef _USER_H_
#define _USER_H_

#include <string>

using namespace std;

// �����
class User {
	int userID;						    // ����� ���� ��ȣ
	string userName;					// ����� �̸�
	string userAddress;					// ����� �ּ�
	string userPhoneNumber;				// ����� ����ó
public:
	// ����� ������ȣ ����(���� ����, �ߺ� X)
	// ����� �̸� ����
	// ����� �ּ� ����
	// ����� ����ó ����
};

// ȸ��
class Member : public User {
	int memberID;						// ȸ�� ID
	int memberPW;						// ȸ�� PassWord
	int mileage;						// ȸ�� ���ϸ���
	int rating;							// ȸ�� ���
public:
	// ȸ�� ID ����
	// ȸ�� ��й�ȣ ����
	// ȸ�� ���ϸ��� ����
	// ȸ�� ��� ����
};

// ��ȸ��
class Guest : public User {
	int guestPW;						// ��ȸ�� ��й�ȣ
public:
	// ��ȸ�� ��й�ȣ ����
};

// ������
class Admin : public User {
	int adminID;						// ������ ID
	int adminPW;						// ������ ��й�ȣ
public:
	// ��ǰ �߰�
	// ��ǰ �԰�
	// ��ǰ ����
	// ��ǰ �˻�
	// ���� �Ⱓ ����
	// ��ǰ ���� ��� ����
	// ���� �ݾ� ��ȸ
	// ȸ�� ���� ����
};

// ȸ�� ����
// �α���
// ��ȸ�� ����


#endif
