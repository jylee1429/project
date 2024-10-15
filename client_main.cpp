#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include "user.h"

#define PORT        8000
#define BUFFER_SIZE 1024
#define LOGIN_SIZE    20

using namespace std;
using json = nlohmann::json;

bool logInClient(string id, string pw);

int main(int argc, char* argv[]) {
    int serverSocket;
    struct sockaddr_in serverAddr;
    const char* serverIp = "127.0.0.1";
    const int serverPort = PORT;
    
    // 소켓 생성
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // 서버 주소 설정
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);

    // 서버에 연결
    if (connect(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection to the server failed");
        close(serverSocket);
        return -1;
    }

    // 클라이언트 종료
    close(serverSocket);
}


// 로그인 함수
bool logInClient(int serverSocket, const string& id, const string& pw) {
    char buffer[LOGIN_SIZE];
    json logInData;
    
    // 데이터 추가
    logInData["command"] = "LOGIN";
    logInData["id"] = id;
    logInData["passwd"] = pw;
    
    // JSON 객체를 문자열로 직렬화
    string serializedData = logInData.dump();

    // 로그인 데이터 전송
    if (send(serverSocket, serializedData.c_str(), serializedData.size(), 0) == -1) {
        perror("send");
        return false;
    }
    // buffer 초기화
    memset(buffer, 0, sizeof(buffer));
    // 서버로부터 응답 수신
    ssize_t size = recv(serverSocket, buffer, sizeof(buffer) - 1, 0);
    if (size == -1) {
        perror("recv");
        return false;
    }
    // 개행 문자나 공백 제거
    buffer[size] = '\0';
    
    json responData;
    try {
        responData = parse(buffer);
    }
    catch (const parse_error& error) {
        cout << "JSON parse error : " << error.what() << endl;
        return false;    
    }

    if(responData.contains("status") && responData["status"] == "SUCCESS") {
        return true;
    }
    else {
        return false;
    }
}

// 회원 가입 함수
bool registerClient(int serverSocket) {
    char buffer[LOGIN_SIZE];
    string serializedMemberInfo = setMemberInfo();

    // 로그인 데이터 전송
    if (send(serverSocket, serializedMemberInfo.c_str(), serializedMemberInfo.size(), 0) == -1) {
        perror("send");
        return false;
    }
    // buffer 초기화
    memset(buffer, 0, sizeof(buffer));    
    // 서버로부터 응답 수신
    ssize_t size = recv(serverSocket, buffer, sizeof(buffer) - 1, 0);
    if (size == -1) {
        perror("recv");
        return false;
    }
    // 개행 문자나 공백 제거
    buffer[size] = '\0';
    json responData;

    try {
        responData = json::parse(buffer);
    }
    catch (const json::parse_error& error) {
        cout << "JSON parse error : " << error.what() << endl;
        return false;    
    }
    // 회원 가입 성공
    if(responData.contains("status") && responData["status"] == "SUCCESS") {
        return true;
    }
    // 회원 가입 실패
    else {
        return false;
    }
}

// 입력된 회원 정보를 직렬화
string setMemberInfo(Member& registerMember) {
    json memberData;

    // 데이터 추가
    memberData["command"] = "REGISTER";
    memberData["memberId"] = "";            // 칸에서 정보 가져오기
    memberData["memberName"] = "";          // 칸에서 정보 가져오기
    memberData["memberAddress"] = "";       // 칸에서 정보 가져오기
    memberData["memberPhoneNumber"] = "";   // 칸에서 정보 가져오기
    memberData["id"] = ;                    // 칸에서 정보 가져오기
    memberData["passwd"] =  ;               // 칸에서 정보 가져오기

    // JSON 객체를 문자열로 직렬화
    string serializedData = memberData.dump();

    return serializedData;
}

