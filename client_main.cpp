#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

using namespace std;

bool exitFlag = false;

void recvMsg(int serverSocket);
void sendMsg(int serverSocket);

int main(int argc, char* argv[]) {
    int serverSocket;
    struct sockaddr_in serverAddr;
    const char* serverIp = argv[1];
    int serverPort = atoi(argv[2]);

    if(argc < 2) {
        return -1;
    }
    // make socket(IPv4 internet protocol, stream socket)
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0) {
        perror("socket");
        return -1;
    }
    // set server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);
    // connect server
    if(connect(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        close(serverSocket);
        return -1;
    }
    // create thread for sending and receiving
    thread thr_recv(recvMsg, serverSocket);
    thread thr_send(sendMsg, serverSocket);
    // wait for thread to finish
    thr_send.join();
    thr_recv.join();
    
    // close client
    close(serverSocket);
}   


void sendMsg(int serverSocket) {
    string msg;
    while(true) {
        // message ?„¤? •
        // log in
        // order
        send(serverSocket, msg.c_str(), msg.size(), 0);
    }
}

void recvMsg(int serverSocket) {
    char recvMsg[1024];

    while(true) {
        ssize_t recvMsgByte = recv(serverSocket, recvMsg, sizeof(recvMsg) - 1, 0);
        if(recvMsgByte < 0) {
            perror("recv");
            break;
        } 
        else if(recvMsgByte == 0) {
            break;
        }
        // message ì²˜ë¦¬
    }
}