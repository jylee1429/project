#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <sqlite3.h>


#define QUEUE_SIZE 50
#define BUFFER_SIZE 1024

using namespace std;
using json = nlohmann::json;
mutex mtx;
sqlite3* db;

void clientHandler(int serverSocket);
void initDB();
void handleLogInUser(int clientSocket, const string& id, const string& passwd);
void handleRegisterClient(int clientSocket, const string& memberId, const string& memberName, const string& memberAddress, const string& memberPhoneNumber, const string& id, const string& passwd);

int main(int argc, char* argv[]) {
    initDB();  // 데이터베이스 초기화
    
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int serverPort = atoi(argv[1]);

    if (argc < 1) {
        return -1;
    }

    // 소켓 생성
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("socket");
        return -1;
    }
    // 주소 설정
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
 
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(serverSocket);
        return -1;
    }
  
    if (listen(serverSocket, QUEUE_SIZE) < 0) {
        perror("listen");
        close(serverSocket);
        return -1;
    }

    while(true) {
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            perror("accept");
            continue;
        }
        // handle client 
        thread clientThread(clientHandler, clientSocket);
        
        clientThread.join();
    }

    close(serverSocket);
}


void clientHandler(int clientSocket) {
    ssize_t size;
    char buffer[BUFFER_SIZE];

    while (true) {
        size = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (size <= 0) {
            perror("recv");
            break;
        }

        buffer[size] = '\0';
        string receiveData = string(buffer);
        string command;
        json requestJson;
        try {
            // JSON 형식으로 파싱
            requestJson = json::parse(receiveData);  
        } 
        catch (const json::parse_error& e) {
            // 잘못된 JSON 데이터는 무시하고 다음 요청 대기
            cerr << "JSON parse error: " << e.what() << endl;
            continue; 
        }

        // 요청 정보 종류 확인
        if (requestJson.contains("command")) {
            string command = requestJson["command"];
            // 로그인 command인 경우
            if (command == "LOGIN") {
                string id = requestJson.value("id", "");
                string password = requestJson.value("passwd", "");
                handleLogInUser(clientSocket, id, password);
            }
            // 회원가입 command인 경우
            else if(command == "REGISTER") {
                string memberId = requestJson.value("memberId", "");
                string memberName = requestJson.value("memberName", "");
                string memberAddress = requestJson.value("memberAddress", "");
                string memberPhoneNumber = requestJson.value("memberPhoneNumber", "");
                string id = requestJson.value("id", "");
                string passwd = requestJson.value("passwd", "");
                handleRegisterClient(clientSocket, memberId, memberName, memberAddress, memberPhoneNumber, id, passwd);
            }
            // 물건 주문 command인 경우
            else if (command == "ORDER") {
                // 주문 처리 로직 추가 필요
            }
            // 물건 정보 확인 command인 경우
            else if (command == "PRODUCT") {
                // 제품 정보 확인 로직 추가 필요
            }
        }
    }
}
// 로그인 처리 함수
void handleLogInUser(int clientSocket, const string& id, const string& passwd) {
    bool isExistUser = false;

    
    mtx.lock();
    string loginSQL = "SELECT COUNT(*) FROM User WHERE id = ? AND passwd = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, loginSQL.c_str(), -1, &stmt, 0) == SQLITE_OK) {
       
        sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, passwd.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            if (count > 0) {
                isExistUser = true;
            }
        }
        else {
            cerr << "SQL execution failed: " << sqlite3_errmsg(db) << endl;
        }
    }
    else {
        cerr << "SQL preparation failed: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    mtx.unlock();

    
    json response;
    if (isExistUser) {
        response["status"] = "SUCCESS";
    }
    else {
        response["status"] = "FAIL";
    }

    string logInData = response.dump();
    if (send(clientSocket, logInData.c_str(), logInData.size(), 0) == -1) {
        perror("send");
    }
}

// 회원가입 처리를 위한 함수
void handleRegisterClient(int clientSocket, const string& memberId, const string& memberName, const string& memberAddress, const string& memberPhoneNumber, const string& id, const string& passwd) {
    bool isRegisterUser = false;

    
    mtx.lock();
    string insertSQL = "INSERT INTO User (memberId, memberName, memberAddress, memberPhoneNumber, id, passwd, mileage, rating) VALUES (?, ?, ?, ?, ?, ?, 0, 1);";  // mileage = 0, rating = bronze(1)
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, memberId.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, memberName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, memberAddress.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, memberPhoneNumber.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, id.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, passwd.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            cout << "New user registered: " << id << endl;
            isRegisterUser = true;
        }
        else {
            cerr << "SQL execution failed: " << sqlite3_errmsg(db) << endl;
        }
    }
    sqlite3_finalize(stmt);
    mtx.unlock();

    
    json response;
    if (isRegisterUser) {
        response["status"] = "SUCCESS";
    }
    else {
        response["status"] = "FAIL";
    }

    string registerData = response.dump();
    send(clientSocket, registerData.c_str(), registerData.size(), 0);
}



// db 초기화 함수
void initDB() {
    if (sqlite3_open("veda2.db", &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return;
    }
    /*
    const char* createTableProduct = R"(
        CREATE TABLE IF NOT EXISTS Products (
            ProductID INTEGER PRIMARY KEY AUTOINCREMENT,
            ProductName TEXT NOT NULL,
            Manufacturer TEXT NOT NULL,
            Price INTEGER NOT NULL,
            Stock INTEGER NOT NULL
        );
    )";
    */
    
    const char* createTableUser = R"(
        CREATE TABLE IF NOT EXISTS User (
            memberID TEXT PRIMARY KEY,
            memberName TEXT NOT NULL,
            memberAddress TEXT NOT NULL,
            memberPhoneNumber INTEGER NOT NULL,
            id TEXT NOT NULL,
            passwd TEXT NOT NULL,
            mileage INT NOT NULL,
            rating INT NOT NULL
        );
    )";


    char* errMsg;
    if (sqlite3_exec(db, createTableUser, 0, 0, &errMsg) != SQLITE_OK) {
        cerr << "User SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}
