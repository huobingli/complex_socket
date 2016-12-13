/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   structClass.h
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午8:50
 */

#include "CacheTable.h"
#include "epoll.h"
#include "onlineDevice.h"
#include "MessageParse.h"
#include "DbControl.h"
#include "serverSocket.h"

#ifndef STRUCTCLASS_H
#define STRUCTCLASS_H

#define MAXSIZE 256

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//互斥锁
//接收缓冲区和发送缓冲区互斥锁
pthread_mutex_t RECVMUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t SENDMUTEX = PTHREAD_MUTEX_INITIALIZER;

//在线列表操作
pthread_mutex_t ONLINEMUTEX = PTHREAD_MUTEX_INITIALIZER;


//接收线程需要epoll socket recvTable
struct _recv_param{
    ServerSocket *serverSt;
    Epoll *serverEpoll;
    CacheTable *pRecvTable;
};

//处理线程需要recvTable analTable onlineTable
//数据处理类，messageParse
struct _anal_param{
    CacheTable *pRecvTable;
    CacheTable *pSendTable;
    OnlineDevice *pOnlineTable;
    DbControl *pDbControl;
    MessageParse *pMessageParse;
};

//发送线程需要sendTable
struct _send_param{
    CacheTable *pSendTable;
};

//在线设备列表
struct _online_param {
    OnlineDevice *pOnlineTable;    
};

#endif /* STRUCTCLASS_H */
