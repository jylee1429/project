#include "user.h"

User::User(string name, string address, int phoneNum)
    : userName(name), userAddress(address), usedPhoneNum(phoneNum) {}

void User::displayInfo() const {
    cout << "User ID: " << userID << endl;
    cout << "Name: " << userName << endl;
    cout << "Address: " << userAddress << endl;
    cout << "Phone Number: " << usedPhoneNum << endl;
}

string User::getUserID() {
    return userID;
