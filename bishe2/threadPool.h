/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   threadPool.h
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午7:56
 */
#include "Thread.h"

#ifndef THREADPOOL_H
#define THREADPOOL_H

class ThreadPool {
private:
    int m_AnalFlag;
    int m_SendFlag;
    int m_OnlineFlag;

    Thread *m_ThreadPool;
    int m_ThreadNum;
public:
    ThreadPool(int iThreadNum);
    ThreadPool(const ThreadPool& orig);
    virtual ~ThreadPool();
    
    int getThreadNum() { return m_ThreadNum; }
    
    void allocThread(void(*callback)(void *arg));
private:

};

#endif /* THREADPOOL_H */

