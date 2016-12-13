/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   threadFuntion.h
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午8:22
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
#include <stdio.h>

#include "CacheTable.h"
#include "epoll.h"
#include "onlineDevice.h"
#include "MessageParse.h"
#include "DbControl.h"
#include "serverSocket.h"
#include "structClass.h"
using namespace std;

static void setNoBlocking(int st) {
    int opts = fcntl(st, F_GETFL);
    if (opts < 0) {
        cout << "fcntl failed " << strerror(errno);
    }

    opts = opts | O_NONBLOCK; // 或运算
    if (fcntl(st, F_SETFL, opts) < 0) {
        cout << "fcntl failed " << strerror(errno);
    }

    cout << "set success" << endl;
}
//接收线程函数需要维护recvTable，
//需要用到的类 
//epoll 类 用来对epoll 进行各种操作
//serversocket类 用于获取服务器端的监听socket，用来epoll收数据
//cacheTable类 接收缓冲区，epoll收到的数据放到该缓冲区中

/************************************************/
static void *Recv(void *arg) {

    cout << "接受线程启动" << endl;

    //canshu
    _recv_param *balabala = (struct _recv_param *) arg;
    ServerSocket *serverSt = (*balabala).serverSt;
    Epoll *serverEpoll = (*balabala).serverEpoll;
    CacheTable *recvTable = (*balabala).pRecvTable;
    int listen_st = serverSt->getst();
    struct epoll_event ev;
    ev.data.fd = listen_st;
    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
    //在epoll池中注册服务器监听socket
    serverEpoll->addEpoll(listen_st, ev);

    int st = 0;

    //客户端地址信息
    struct sockaddr_in clinetSockaddr;
    //客户端消息buffer
    char buffer[MAXSIZE];
    //客户端消息长度
    int recvLength = 0;
    //epoll里的文件描述符
    int fd;
    while (1) {
        int nfds = serverEpoll->waitEpoll(-1);
        cout<<"nfds : "<<nfds<<endl;
        if (nfds == -1) {
            cout << "epoll wait failed" << strerror(errno);
            break;
        }


        for (int i = 0; i < nfds; i++) {
            fd = serverEpoll->getfd(i);
		cout<<fd<<endl;
            if (fd < 0) {
                continue;
            }
            if (fd == listen_st) {
                cout << "监测到一个socket链接" << endl;
                //服务器接收到客户端请求，并生成服务器端的客户端socket
                st = serverSt->acceptSocket(listen_st, clinetSockaddr);

                //成功生成服务器端socket,注册到epoll池中
                if (st > 0) {
                    setNoBlocking(st);
                    ev.data.fd = st;
                    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
                    serverEpoll->addEpoll(st, ev);
                    continue;
                }
            }
            __uint32_t events = serverEpoll->getEvent(i);
            st = serverEpoll->getfd(i);

            //socket get data
            if (events & EPOLLIN) {

                //接收数据开始
                cout << "recv from : " << st << endl;
                memset(&buffer, 0, sizeof (buffer));
                recvLength = serverSt->recvSocket(st, buffer);
                //接收数据完成

                //数据为空
                if (strlen(buffer) <= 0) {
                    //serverSt->sendSocket(st);
                    close(st);
                } else {
                    cout << "recv buffer : " << buffer << endl;
                    //将接收到的数据转换成服务器数据结构
                    //放入接收缓冲区
                    cacheNode *tempNode = new cacheNode();
                    tempNode->iSt = st;
                    tempNode->iBufferLength = recvLength;
                    memcpy(tempNode ->cBuffer, buffer, recvLength);
                    tempNode->cOperate = 0x00;
                    tempNode->pNextNode = NULL;
                    tempNode->pPriorNode = NULL;

                    //插入队列加锁
                    pthread_mutex_lock(&RECVMUTEX);
                    //插入到接收缓冲
                    recvTable->insertTable(tempNode);
                    //插入完成解锁
                    pthread_mutex_unlock(&RECVMUTEX);
		    cout<<"已经放入到接收缓冲"<<endl;
                }
            }
            //socket error
            if (events & EPOLLERR) {
                st = serverSt->acceptSocket(listen_st, clinetSockaddr);
                close(st);
            }
            //socket unlinked
            if (events & EPOLLHUP) {
                st = serverSt->acceptSocket(listen_st, clinetSockaddr);
                close(st);
            }
        }
    }
}
/************************************************/

//sendThread

/************************************************/
static void *Send(void *arg) {
    cout << "发送线程启动" << endl;
    _send_param *balabala = (struct _send_param *) arg;
    CacheTable *sendTable = (*balabala).pSendTable;
    int sendSt = 0;
    char buffer[MAXSIZE];

    //线程死循环
    while (1) {
        if (sendTable->getNodeNum() > 0) {
            cout << "有" << sendTable->getNodeNum() << "条要发送" << endl;

            pthread_mutex_lock(&SENDMUTEX);
            cout << "发送队列已经加锁， 正在获取取发送数据" << endl;
            cacheNode *tempNode = sendTable->getEndNode();
            pthread_mutex_unlock(&SENDMUTEX);
            cout << "发送队列已经解锁， 已经取得发送数据" << endl;

            //设置参数
            sendSt = tempNode->iSt;
	    sendSt = 5;
            //使用前清空
            memset(&buffer, 0, MAXSIZE);
            memcpy(buffer, "收到了数据", 6);
            memcpy(buffer, tempNode->cBuffer, tempNode->iBufferLength);

            send(sendSt, buffer, strlen(buffer), 0);

            cout << "已经向" << sendSt << "发送了" << buffer << endl;
        } else {
            sleep(2);
        }
    }
}
/************************************************/

//analyzeThread

/************************************************/
static void *Anal(void *arg) {
    cout << "处理线程启动" << endl;
    struct _anal_param *balabala = (struct _anal_param *) arg;
    CacheTable *sendTable = (*balabala).pSendTable;
    CacheTable *recvTable = (*balabala).pRecvTable;
    OnlineDevice *onlineTable = (*balabala).pOnlineTable;
    DbControl *dbControl = (*balabala).pDbControl;
    MessageParse *messageParse = (*balabala).pMessageParse;

    int updateDeviceNo = 0;
    while (1) {
        cout << "anal->sendTableNodeNum" << sendTable->getNodeNum() << endl;
        cout << "anal->recvTableNodeNum" << recvTable->getNodeNum() << endl;
        if (recvTable->getNodeNum() > 0) {

            pthread_mutex_lock(&RECVMUTEX);
            cout << "正在处理一条信息" << endl;
            //获得接收列表最后一个节点
            cacheNode *tempNode = recvTable->getEndNode();
            pthread_mutex_unlock(&RECVMUTEX);

            //如果buffer第二位是0x00表示是客户端心跳
	    cout<<"tempNode->cBuffer"<<tempNode->cBuffer<<endl;
	    cout<<tempNode->cBuffer[1]<<endl;
            if (tempNode->cBuffer[1] == '0') {
		cout<<"心跳"<<endl;
                send(5, "心跳", 3, 0);
		//返回值如果是-1表示没有在在线列表中找到同一个设备
                //表示新设备，需要添加
                updateDeviceNo = onlineTable->scanSameDevice(tempNode->iSt);
                if (updateDeviceNo == -1) {               
                    //messageParse->analyzeDevice(tempNode, newDevice);

                    //_onlineDevice *newDevice = new _onlineDevice();
                    //onlineTable->insertDevice(newDevice);
                } else {
                    //不是新设备，直接覆盖原来的数据
                    //messParse->analyzeDevice(tempNode, )
                }
            }//普通数据包
            else {
                cacheNode *sendNode = new cacheNode();

                memset(&sendNode->cBuffer, 0, sendNode->iBufferLength);
                memcpy(sendNode->cBuffer, tempNode->cBuffer, tempNode->iBufferLength);

                //对buffer进行处理
                //messageParse->analyzeMessage(tempNode, sendNode);

                //处理完后增加其他信息
                //
                pthread_mutex_lock(&SENDMUTEX);
                cout << "正在加入发送队列" << endl;
                sendTable->insertTable(sendNode);
                pthread_mutex_unlock(&SENDMUTEX);
                cout << "添加完成" << endl;
            }
        } else {
	    cout<<"没东西，睡觉！！"<<endl;
            sleep(2);
	
        }
    }
    cout << "处理线程退出" << endl;
}
/************************************************/

//heartBreatThraed

/************************************************/
/*
static void *heartBreath(void *arg) {

    classpoint *newPoint = (classpoint*) arg;

    //test
    threadPool *threadPool = newPoint->pThreadPool;

    while (1) {
        //cout<<"threadNum"<<threadPool->getThreadNum()<<endl;
        sleep(4);
        // cout<<"sendTableNodeNum"<<sendTable->getNodeNum()<<endl;
        // cout<<"recvTableNodeNum"<<recvTable->getNodeNum()<<endl;
        cout << "---------------heartBreath---------------" << endl;


        if (recvTable->getNodeNum() != 0) {
            cout << "应该启动分析线程" << endl;
            newPoint->pThreadPool->allocThread(epollAnalyze);
        } else {
            cout << "321321321321321" << endl;
        }

        if (sendTable->getNodeNum() != 0) {
            cout << "应该启动发送线程" << endl;
            newPoint->pThreadPool->allocThread(epollSend);
        } else {
            cout << "123123123123123" << endl;
        }

        //cout<<"show thread flag info"<<endl;
        // for(int  i = 0; i  <  3; i++){
        // 	//cout<<threadPool[i]->getThread()<<endl;
        // }
        cout << "-------------end heartBreath-------------" << endl;
    }
}*/
/************************************************/

//thread init
/************************************************/
/*
static void *initRun(void *arg) {

    while (1) {
        pthread_mutex_lock(&mutex);
        cout << "hello " << endl;
        // while(sendTable->getNodeNum() == 0 || recvTable->getNodeNum() != 0) {

        // 	cout<<"fuck linux"<<endl;
        // 	pthread_cond_wait(&cond, &mutex);
        // 	sleep(5);
        // }
        while (runnerTail == NULL) {
            cout << "等待cond信号" << endl;
            pthread_cond_wait(&cond, &mutex);
            cout << "接收cond信号" << endl;
        }
        pthread_mutex_unlock(&mutex);
        //cout<<"101010"<<endl;

        serverAnal *analyze = (serverAnal *) malloc(sizeof (serverAnal));
        analyze->pSendTable = sendTable;
        analyze->pRecvTable = recvTable;
        // cout<<analyze->pSendTable->getNodeNum()<<endl;
        runnerTail->arg = analyze;
        (runnerTail->callback)(runnerTail->arg);
        free(runnerTail);
        //(newCallBack->callback)(newCallBack->arg);

        sleep(10);
    }
}*/
/************************************************/


//onlineDeviceThraed
/************************************************/

/************************************************/


