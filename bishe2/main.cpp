/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午7:52
 */

#include <cstdlib>
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
using namespace std;

#include "epoll.h"
#include "CacheTable.h"
#include "onlineDevice.h"
#include "serverSocket.h"
#include "threadControl.h"
#include "structClass.h"
#include "MessageParse.h"
#include "DbControl.h"
#include "threadFuntion.h"

/*
void setNoBlocking(int st)
{
	int opts = fcntl(st, F_GETFL);
	if(opts <0)
	{
		cout<<"fcntl failed "<< strerror(errno);
	}

	opts = opts | O_NONBLOCK; // 或运算
	if(fcntl(st, F_SETFL, opts) < 0)
	{
		cout<<"fcntl failed "<< strerror(errno);
	}

	cout<<"set success"<<endl;
}
*/
CacheTable *GRecvTable;
CacheTable *GSendTable;
OnlineDevice *GOnlineDevice;

/*
 * 
 */
int main(int argc, char** argv) {

    pthread_t recvThread;
    pthread_t analThread;
    pthread_t sendThread;
    pthread_t onlineThread;
    
    GRecvTable = new CacheTable(20);
    GSendTable = new CacheTable(20);

    GOnlineDevice = new OnlineDevice(5);
    
    
    Epoll *serverEpoll = new Epoll(100);
    serverEpoll->createEpoll();
//    cout<<&serverEpoll<<endl;
    cout<<GRecvTable<<endl;
    ServerSocket *listenSocket = new ServerSocket(10000);
    listenSocket->createServerSocket();
    int listenSt = listenSocket->getst();
    //设置为非阻塞soket
    setNoBlocking(listenSt);
    MessageParse *messageParse= new MessageParse();
    DbControl *dbControl = new DbControl();
    
    _recv_param recvParam;
    _anal_param analParam;
    _send_param sendParam;
    _online_param onlineParam;
    
    recvParam.pRecvTable = GRecvTable;
    recvParam.serverEpoll = serverEpoll;
    recvParam.serverSt = listenSocket;
    
    analParam.pRecvTable = GRecvTable;
    analParam.pSendTable = GSendTable;
    analParam.pMessageParse = messageParse;
    analParam.pOnlineTable = GOnlineDevice;
    analParam.pDbControl = dbControl;
    
    sendParam.pSendTable = GSendTable;

    onlineParam.pOnlineTable = GOnlineDevice;
    
    pthread_create(&recvThread, NULL, Recv, &recvParam);
    pthread_create(&analThread, NULL, Anal, &analParam);
    pthread_create(&sendThread, NULL, Send, &sendParam);
    pthread_create(&onlineThread, NULL, Online, onlineParam);
    cout<<"1"<<endl;
    while(1) {}
    return 0;

}

