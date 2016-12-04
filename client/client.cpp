
//*****************************************************
//
//    FileName:      client.cpp
//
//    Author:         huobingli - huobingli@outlook.com
//    Description:    
//    Create:        2016-12-03 21:06:43
//    Last Modified: 2016-12-03 21:06:43
//****************************************************
//
#include <iostream>
#include "clientSocket.cpp"

_socket_param *st;

int main(int arg, char *argv[]) {
     if(arg < 2) return 0;
     std::cout<<argv[1]<<std::endl;
     std::cout<<argv[2]<<std::endl;
     char IPAddress[16];
     int Port = atoi(argv[2]);
     memset(IPAddress, 0, sizeof(IPAddress));
     memcpy(IPAddress,argv[1], strlen(argv[1]));
     
     clientSocket *client = new clientSocket();
     client->setIPPort(IPAddress, strlen(IPAddress), Port);
    
     client->createSocket();
     client->connectServer();
     std::cout<<"111"<<std::endl;
     st = (_socket_param*)malloc(sizeof(_socket_param));
     pthread_t threadSend;
     pthread_t threadRecv;
     
     client->judgeFlag(); 
     st->_clientSocket = client->getSt(); 
     pthread_create(&threadSend, NULL, clientSocket::sendSocket, st);
     pthread_create(&threadRecv, NULL, clientSocket::recvSocket, st);
     
     while(1) {}
     pthread_join(threadRecv, NULL);
     //free(st);
     return 0;
}
