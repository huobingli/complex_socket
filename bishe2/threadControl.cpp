/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   threadControl.cpp
 * Author: 炳雳
 * 
 * Created on 2016年12月8日, 下午7:56
 */

#include "threadControl.h"


ThreadControl::ThreadControl(int iThreadNum) {
    m_WorkQueue = new workQueue();
    m_ThreadPool = new ThreadPool(iThreadNum);
    
    m_ThreadNum = iThreadNum;
    m_Shutdown = false;    
}

ThreadControl::ThreadControl(const ThreadControl& orig) {
}

ThreadControl::~ThreadControl() {
    delete m_WorkQueue;
    delete m_ThreadPool;
}

