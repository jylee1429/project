#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

class User {
protected:
    string userID;
    string userName;
    string userAddress;
    int usedPhoneNum;

public:
    User(string name, string address, int phoneNum);

    virtual void displayInfo() const;
    string getUserID();
};

#endif
