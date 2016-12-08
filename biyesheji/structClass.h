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

#include "cacheTable.h"
#include "epoll.h"
#include "onlineDevice.h"
#ifndef STRUCTCLASS_H
#define STRUCTCLASS_H

#define MAXSIZE 256

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct _recv_param{
    serverSocket *serverSt;
    epoll *serverEpoll;
    cacheTable *pRecvTable;
};
struct _anal_param{
    cacheTable *pRecvTable;
    cacheTable *pAnalTable;
};
struct _send_param{
    cacheTable *pSendTable;
};

struct _heart_param{
    
};
#endif /* STRUCTCLASS_H */
