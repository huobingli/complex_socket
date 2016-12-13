/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Thread.h
 * Author: 炳雳
 *
 * Created on 2016年12月9日, 上午10:52
 */

#include <iostream>
using namespace std;

#ifndef THREAD_H
#define THREAD_H

class Thread {
private:
    pthread_t m_PThread;
    pthread_attr_t m_Pthread_attr_t;
    int m_Flag;
public:
    Thread();
    Thread(const Thread& orig);
    virtual ~Thread();
    //init pThread
    void initThread();

    int getFlag() { return m_Flag; }

    void turnFlag() { m_Flag = (m_Flag == 0) ? 1 : 0; }
};
#endif /* THREAD_H */

