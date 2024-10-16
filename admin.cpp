#include "admin.h"
#include <iostream>

Admin::Admin(int id, int pw) : adminID(id), adminPW(pw), db(nullptr) {}

void Admin::initDB() {
    if (sqlite3_open("veda.db", &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    const char* createTableProduct = R"(
        CREATE TABLE IF NOT EXISTS Products (
            ProductID INTEGER PRIMARY KEY AUTOINCREMENT,
            ProductName TEXT NOT NULL,
            Manufacturer TEXT NOT NULL,
            Price INTEGER NOT NULL,
            Stock INTEGER NOT NULL
        );
    )";
    const char* createTableUser = R"(
        CREATE TABLE IF NOT EXISTS User (
            userID TEXT PRIMARY KEY,
            userName TEXT NOT NULL,
            userAddress TEXT NOT NULL,
            userPhoneNum INTEGER NOT NULL,
            ID TEXT NOT NULL,
            PW TEXT NOT NULL,
            mileage INT NOT NULL,
            rating INT NOT NULL
        );
    )";

    char* errMsg;
    if (sqlite3_exec(db, createTableProduct, 0, 0, &errMsg) != SQLITE_OK) {
        cerr << "Product SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    if (sqlite3_exec(db, createTableUser, 0, 0, &errMsg) != SQLITE_OK) {
        cerr << "User SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void Admin::addProduct(const string& productName, const string& manufacturer, int price, int stock) {
    string insertSQL = "INSERT INTO Products (ProductName, Manufacturer, Price, Stock) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, productName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, manufacturer.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, price);
        sqlite3_bind_int(stmt, 4, stock);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Execution failed: " << sqlite3_errmsg(db) << endl;
        }
        else {
            cout << "Product added: " << productName << endl;
        }
    }
    else {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmt);
}
// 상품 조회
void Admin ::listProducts() const {
    const char* selectSQL = "SELECT * FROM Products;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int productID = sqlite3_column_int(stmt, 0);
            const char* productName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* manufacturer = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int price = sqlite3_column_int(stmt, 3);
            int stock = sqlite3_column_int(stmt, 4);

            cout << "Product ID: " << productID << ", Name: " << productName
                << ", Manufacturer: " << manufacturer
                << ", Price: " << price
                << ", Stock: " << stock << endl;
        }
    }
    else {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmt);
}
// 상품 삭제
void Admin::deleteProduct(int productID) {
    const char* deleteSQL = "DELETE FROM Products WHERE ProductID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, deleteSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, productID);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            cout << productID << " deleted successfully." << endl;
        }
        else {
            cerr << "Delete failed: " << sqlite3_errmsg(db) << endl;
        }
    }
    else {
        cerr << "SQL prepare failed: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}
//상품 재고 수정
void Admin::modifyStock(int productID, int newStock) {
    const char* modifyStock = "UPDATE Products SET Stock = ? WHERE ProductID = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, modifyStock, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, newStock);
        sqlite3_bind_int(stmt, 2, productID);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            cout << productID << " stock modified successfully." << endl;
        }
        else {
            cerr << "Modify failed: " << sqlite3_errmsg(db) << endl;
        }
    }
    else {
        cerr << "SQL prepare failed: " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmt);
}
// 회원 조회
void Admin::listMember() const {
    const char* selectSQL = "SELECT * FROM User;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* userID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            const char* userName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* userAddress = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int userPhoneNum = sqlite3_column_int(stmt, 3);
            const char* id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            const char* pw = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            int mileage = sqlite3_column_int(stmt, 6);
            int rating = sqlite3_column_int(stmt, 7);

            cout << "User ID: " << userID
                << ", Name: " << userName
                << ", Address: " << userAddress
                << ", Phone Number: " << userPhoneNum
                << ", ID: " << id
                << ", Mileage: " << mileage
                << ", Rating: " << rating << endl;
        }
    }
    else {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmt);
}

// 회원 rating 수정
void Admin::modifyMemberRating(const string& userID, int newRating) {
    const char* modifySQL = "UPDATE User SET rating = ? WHERE userID = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, modifySQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, newRating);
        sqlite3_bind_text(stmt, 2, userID.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            cout << userID << " modified successfully." << endl;
        }
        else {
            cerr << "Modify failed: " << sqlite3_errmsg(db) << endl;
        }
    }
    else {
        cerr << "SQL prepare failed: " << sqlite3_errmsg(db) << endl;
    }
}

void Admin::closeDB() {
    sqlite3_close(db);
}
