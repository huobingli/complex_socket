/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serverSocket.h
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午7:54
 */

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H


class ServerSocket {
private:
    int m_Socket;
    int m_Port;
public:
    ServerSocket(int iPort);

    ~ServerSocket();
    
    int getst() { return m_Socket; }
    
    void createServerSocket();

    int acceptSocket(int iListenSt, struct sockaddr_in &sSockaddr);

    void sendSocket(int st);

    int recvSocket(int ist, char *buffer);
	
};

#endif /* SERVERSOCKET_H */

