/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   workQueue.cpp
 * Author: 炳雳
 * 
 * Created on 2016年12月9日, 上午10:18
 */

#include "workQueue.h"

workQueue::workQueue() {
    m_HeadNode = NULL;
    m_EndNode = NULL;
}

workQueue::workQueue(const workQueue& orig) {
}

workQueue::~workQueue() {
}

void workQueue::insertWork(workNode *pWorkNode) {
    if (empty()) {
        m_EndNode = pWorkNode;
        m_HeadNode = pWorkNode;
    } else {
        workNode *tempNode = m_EndNode;
        m_EndNode = pWorkNode;
        tempNode->nextWork = m_EndNode;
    }
}

workNode *workQueue::getWork() {
    if (empty()) {
        return NULL;
    } else {
        workNode *tempNode = m_HeadNode;
        m_HeadNode = tempNode->nextWork;
        tempNode->nextWork = NULL;
        return tempNode;
    }
}