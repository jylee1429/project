#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

#define QUEUE_SIZE 50
#define BUFFER_SIZE 1024

using namespace std;
using json = nlohmann::json;

void clientHandler(int serverSocket);

int main(int argc, char* argv[]) {
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

void handleLogInUser(int clientSocket, const string& id, const string& password) {
    bool isExistUser = false;

    /*
    데이터 베이스 이용해서 해당 데이터가 있는지 확인
    있으면 isExistUser = true;
    없으면 isExistUser = false;
    */

    // 로그인 결과를 JSON 형식으로 생성
    json response;

    if (isExistUser) {
        response["status"] = "SUCCESS";
    } 
    else {
        response["status"] = "FAIL";
    }

    // JSON 응답 메시지를 문자열로 직렬화하여 전송
    string logInData = response.dump();
    if (send(clientSocket, logInData.c_str(), logInData.size(), 0) == -1) {
        perror("send");
        return false;
    }
}

// 회원가입 처리를 위한 함수
void handleRegisterClient(int clientSocket, const string& memberId, const string& memberName, const string& memberAddress, const string& memberPhoneNumber, const string& id, const string& passwd) {
    bool isRegisterUser = false;

    /*
    데이터베이스를 이용하여 회원 정보를 저장하고 등록 성공 여부를 isRegisterUser에 설정
    ranking = bronze, 마일리지 = 0으로 초기화
    */

    // 회원가입 결과를 클라이언트에 전송
    json response;
    if (isRegisterUser) {
        response["status"] = "SUCCESS";
    } else {
        response["status"] = "FAIL";
    }

    string registerData = response.dump();
    send(clientSocket, registerData.c_str(), registerData.size(), 0);
}