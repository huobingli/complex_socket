/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   workQueue.h
 * Author: 炳雳
 *
 * Created on 2016年12月9日, 上午10:18
 */
#include <iostream>
using namespace std;


struct workNode {
    void (*callback)(void *arg);
    void *arg;
    struct workNode *nextWork;
};

#ifndef WORKQUEUE_H
#define WORKQUEUE_H

class workQueue {
private:
    workNode *m_HeadNode;
    workNode *m_EndNode;
    
    bool empty() { return (m_HeadNode == NULL && m_EndNode == NULL); }
public:
    workQueue();
    workQueue(const workQueue& orig);
    virtual ~workQueue();
    
    void insertWork(workNode *pWorkNode);
    
    workNode *getWork();
};

#endif /* WORKQUEUE_H */

