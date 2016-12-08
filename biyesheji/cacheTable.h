/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cacheTable.h
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午7:55
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


struct cacheNode {
    int iSt;
    struct sockaddr_in sSockaddr;
    char cOperate;
    char cBuffer[256];
    int iBufferLength;
    cacheNode *pNextNode;
    cacheNode *pPriorNode;
};

#ifndef CACHETABLE_H
#define CACHETABLE_H

class cacheTable {
private:
    cacheNode *m_HeadNode;
    cacheNode *m_EndNode;
    
    int m_NodeNum;
    int m_TotalNum;
    
    bool empty() { return m_NodeNum == 0; }
    bool full() { return m_NodeNum == m_TotalNum; }
    
public:
    cacheTable(int iNum);
    cacheTable(const cacheTable& orig);
    virtual ~cacheTable();
    
    //插入表
    bool insertTable(cacheNode *pCacheNode);
    //得到节点
    cacheNode *getEndNode();
    
    int getNodeNum() { return m_NodeNum; }

    
};

#endif /* CACHETABLE_H */

