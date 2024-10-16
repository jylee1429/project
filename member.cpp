#include "member.h"
#include <iostream>
#include <cstdlib>

int randomNum(unordered_set<int>& usedNum) {
    int number;
    do {
        number = rand() % 10000;
    } while (usedNum.find(number) != usedNum.end());
    usedNum.insert(number);
    return number;
}

Member::Member(string name, string address, int phoneNum, string id, string pw, unordered_set<int>& usedNum)
    : User(name, address, phoneNum), memberID(id), memberPW(pw), mileage(0), rating(0) {
    userID = "m" + to_string(randomNum(usedNum));
}

void Member::displayInfo() const {
    User::displayInfo();
    cout << "Member ID: " << memberID << endl;
    cout << "Mileage: " << mileage << endl;
    cout << "Rating: " << rating << endl;
}

string Member::getPassword() const {
    return memberPW;
}

int Member::getRating() const {
    return rating;
}

void Member::setRating(int newRating) {
    rating = newRating;
}

Guest::Guest(string name, string address, int phoneNum, string pw, unordered_set<int>& usedNum)
    : User(name, address, phoneNum), guestPW(pw) {
    userID = "g" + to_string(randomNum(usedNum));
}

void Guest::displayInfo() const {
    User::displayInfo();
    cout << "Guest Password: " << guestPW << endl;
}
