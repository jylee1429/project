#ifndef ADMIN_H
#define ADMIN_H

#include <sqlite3.h>
#include <string>
#include <unordered_set>

using namespace std;

class Admin {
private:
    int adminID;
    int adminPW;
    sqlite3* db;

public:
    Admin(int id, int pw);
    //void initDB();
    void addProduct(const string& productName, const string& manufacturer, int price, int stock);
    void listProducts() const;
    void deleteProduct(int productID);
    void modifyStock(int productID, int newStock);
    void listMember() const;
    void modifyMemberRating(const string& userID, int newRating);
    void closeDB();
};

#endif

