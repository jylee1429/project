#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

#define QUEUE_SIZE 128

using namespace std;

void handleClient(int clientSocket);
void sendMsg(int serverSocket);
void recvMsg(int serverSocket);

int main(int argc, char* argv[]) {
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int serverPort = atoi(argv[1]);

    if(argc < 1) {
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
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    // bind server socket
    if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(serverSocket);
        return -1;
    }
    // listen incoming connection
     if(listen(serverSocket, QUEUE_SIZE) < 0) {
        perror("listen");
        close(serverSocket);
        return -1;
    }

    while(true) {
        // accept incoming connection
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if(clientSocket < 0) {
            perror("accept");
            continue;
        }
        // handle client 
        handleClient(clientSocket);
    }

    close(serverSocket);
}

void handleClient(int clientSocket) {
    // create thread for sending and receiving
    thread thr_recv(recvMsg, clientSocket);
    thread thr_send(sendMsg, clientSocket);

    // wait for thread to finish
    thr_send.join();
    thr_recv.join();

    close(clientSocket);
}

void sendMsg(int serverSocket) {
}

void recvMsg(int serverSocket) {
}