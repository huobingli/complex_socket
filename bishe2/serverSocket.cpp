/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serverSocket.cpp
 * Author: 炳雳
 * 
 * Created on 2016年12月8日, 下午7:54
 */

#include "serverSocket.h"

ServerSocket::ServerSocket(int iPort) {
    m_Socket = 0;
    m_Port = iPort;
}

ServerSocket::~ServerSocket() {
}

void ServerSocket::createServerSocket() {
    m_Socket = socket(AF_INET, SOCK_STREAM, 0);
    int on = 1;
    if (setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        cout << "setsockopt failed " << strerror(errno);
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_Port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(m_Socket, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        cout << "bind port " << m_Port << "failed" << strerror(errno) << endl;
    }
    if (listen(m_Socket, 300) == -1) {
        cout << "listen failed " << strerror(errno);
    }
}

int ServerSocket::acceptSocket(int iListenSt, struct sockaddr_in &sSockaddr) {
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    memset(&client_addr, 0, sizeof(client_addr));
    
    int client_st = accept(iListenSt, (struct sockaddr *) &client_addr, &len);
    
    memcpy(&sSockaddr, (struct sockaddr_in *)&client_addr, len);
    cout<<client_st<<endl;  
    if (client_st < 0) {
        cout << "accept failed" << strerror(errno);
    }
    else {
        cout << "accept by" << inet_ntoa(client_addr.sin_addr);
    }
    return client_st;
}

void ServerSocket::sendSocket(int st) {
    char s[] = "link success";
    send(st, s, strlen(s), 0);
}

int ServerSocket::recvSocket(int ist, char *buffer) {
    char recvBuffer[256];
    memset(recvBuffer, 0, sizeof(recvBuffer));
    ssize_t rc = recv(ist, recvBuffer, sizeof(recvBuffer), 0);
    recvBuffer[rc + 1] = '\0';
    //cout << "recv data rc NUM: " << rc << endl;
    if (rc <= 0) {
        cout << "recv failed " << strerror(errno) << endl;
        return 0;
    } else {
        memcpy(buffer, recvBuffer, rc);
        return rc;
    }
    //else {
    //    send(ist, recvBuffer, rc, 0);
    //}
    //cout <<"recv data" << recvBuffer << endl;
}

