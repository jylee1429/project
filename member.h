#ifndef MEMBER_H
#define MEMBER_H

#include "user.h"
#include <unordered_set>
#include <string>
using namespace std;

class Member : public User {
private:
    string memberID;
    string memberPW;
    int mileage;
    int rating;

public:
    Member(string name, string address, int phoneNum, string id, string pw, unordered_set<int>& usedNum);

    void displayInfo() const override;
    string getPassword() const;
    int getRating() const;
    void setRating(int newRating);
};

class Guest : public User {
private:
    string guestPW;

public:
    Guest(string name, string address, int phoneNum, string pw, unordered_set<int>& usedNum);

    void displayInfo() const override;
};

#endif

