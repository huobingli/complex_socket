/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   threadControl.h
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午7:56
 */

#include "workQueue.h"
#include "threadPool.h"

#ifndef THREADCONTROL_H
#define THREADCONTROL_H

class ThreadControl {
private:
    workQueue *m_WorkQueue;
    ThreadPool *m_ThreadPool;
    
    int m_ThreadNum;
    bool m_Shutdown;
public:
    ThreadControl(int iThreadNum);
    ThreadControl(const ThreadControl& orig);
    virtual ~ThreadControl();
    
    //得到缓冲池指针
    ThreadPool *getThreadPool() { return m_ThreadPool; }
    
    bool releaseThreadPool(){ return true; }
private:

};

#endif /* THREADCONTROL_H */

