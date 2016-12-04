
//********************************************************
//
//       FileName:      clientSocket.cpp
//
//       Author:  huobingli - huobingli@outlook.com
//       Description:    
//       Create: 2016-12-02  12:49:32
//       Last Modified: 2016-12-02 12:49:32
//********************************************************
// 
#include <iostream>
#include <time.h>
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
#include <pthread.h>


#ifndef _CLIENTSOCKET_CPP
#define _CLIENTSOCKET_CPP
static int flag = 0;

struct _socket_param {
  int _clientSocket;
};

class clientSocket {
private:
  bool m_Connected;
  struct sockaddr_in m_ClientAddr;
  int m_Socket;
  int m_Port;
  unsigned char m_IPAddress[16];
public:
  clientSocket() {
    m_Socket = 0;
    m_Port = 0;
    m_Connected = false;
    memset(m_IPAddress, 0, sizeof(m_IPAddress));
    memset(&m_ClientAddr, 0, sizeof(m_ClientAddr));
  }
  ~clientSocket() { }
  
  void setIPPort(char *pIPAddress, int iIPLength, int iPort) {
    memcpy((char *)m_IPAddress, pIPAddress, iIPLength);
    m_Port = iPort;
  }

  bool createSocket() {
    m_Socket = socket(AF_INET, SOCK_STREAM, 0);
    int on = 1;
    if(setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
      std::cout<<"setsocket failed"<<strerror(errno)<<std::endl;
    } else { std::cout<<"createSocket successed!! socket is "<<m_Socket<<std::endl; }
  }
  
  bool connectServer() {
    m_ClientAddr.sin_family = AF_INET;
    m_ClientAddr.sin_port = htons(m_Port);
    m_ClientAddr.sin_addr.s_addr = inet_addr((char*)m_IPAddress);
    
    std::cout<<"IP"<<m_IPAddress<<std::endl;
    std::cout<<"sizeof"<<strlen((char*)m_IPAddress)<<std::endl;
    int iConnect = connect(m_Socket, (struct sockaddr *) &m_ClientAddr, sizeof(m_ClientAddr));
    std::cout<<iConnect<<std::endl;
    if(iConnect == 0) {
       std::cout<<"connect server successed!!  my socket is "<<m_Socket<<std::endl;
       m_Connected = true;
       return m_Connected;
    } else if (iConnect == -1) {
       std::cout<<"connect failed ..."<<strerror(errno)<<std::endl;
       close(m_Socket);
       return m_Connected;
    } else {
       close(m_Socket);
       return m_Connected;
    }
  }

  void judgeFlag() {
    if(m_ClientAddr.sin_family != 0 && m_Connected) {
       flag= 1;
    } else {
       flag = 0;
    }
  }
  int getSt() { return m_Socket; }
  static void *sendSocket(void *arg) {
     std::cout<<"发送启动"<<std::endl;
     int st = *(int *)arg;
     std::cout<<st<<std::endl;    
     char sendBuffer[128];
     
     while(1) {
       if(flag == 0) break;
       memset(sendBuffer, 0, sizeof(sendBuffer));
       read(STDIN_FILENO, sendBuffer, sizeof(sendBuffer));
       strcat(sendBuffer, "\0");

       send(st, sendBuffer, strlen(sendBuffer), 0);
     }
     std::cout<<111<<std::endl;
  }

  static void *recvSocket(void *arg) {
     std::cout<<"接收启动"<<std::endl;
     time_t timep;
     time(&timep);
     int st = *(int *)arg;
     char recvBuffer[128];

     while(1) {
       if(flag == 0) break;
       memset(recvBuffer, 0, sizeof(recvBuffer));
       int rc = recv(st, recvBuffer, sizeof(recvBuffer), 0);
       if(rc < 0 ) break;
       std::cout<<ctime(&timep)<<"recieve data"<<recvBuffer<<std::endl;
     }
  }
};


#endif
