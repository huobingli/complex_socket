/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cacheTable.cpp
 * Author: 炳雳
 * 
 * Created on 2016年12月8日, 下午7:55
 */

#include "cacheTable.h"

cacheTable::cacheTable(int iNum) {
    m_NodeNum = 0;
    m_TotalNum = iNum;
    m_HeadNode = NULL;
    m_EndNode = NULL;
}

cacheTable::cacheTable(const cacheTable& orig) {
    
}

cacheTable::~cacheTable() {
    m_HeadNode = NULL;
    m_EndNode = NULL;
}

bool cacheTable::insertTable(cacheNode *pCacheNode) {
    if (full()) { return false; }
    else {
        if (empty()) {
            m_HeadNode = pCacheNode;
            m_EndNode = pCacheNode;
            pCacheNode->pNextNode == NULL;
        }
        else {
            cacheNode *tempNode = m_HeadNode;
            //insert node
            m_HeadNode = pCacheNode;
            pCacheNode->pNextNode = pCacheNode;
            tempNode->pPriorNode = pCacheNode;
        }
        ++m_NodeNum;
        return true;
    }
}

cacheNode *cacheTable::getEndNode() {
    if (empty()) {
        return NULL;
    }
    else if (m_NodeNum > 1) {
        cacheNode *tempEndNode = m_EndNode;
        m_EndNode = m_EndNode->pNextNode;
        m_EndNode->pNextNode = NULL;
        tempEndNode->pPriorNode = NULL;
        m_NodeNum--;
        return tempEndNode;
    }
    else if (m_NodeNum = 1) {
        cacheNode *tempEndNode = m_EndNode;
        m_EndNode = NULL;
        m_HeadNode = NULL;
        m_NodeNum--;
        return tempEndNode;
    }
}