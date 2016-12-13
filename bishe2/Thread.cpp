/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Thread.cpp
 * Author: 炳雳
 * 
 * Created on 2016年12月9日, 上午10:52
 */

#include "Thread.h"

Thread::Thread() {
    m_Flag = 0;
}

Thread::Thread(const Thread& orig) {
}

Thread::~Thread() {
}

void Thread::initThread() {
    //初始化线程的属性
    pthread_attr_init(&m_Pthread_attr_t);
    //设置脱离状态的属性(决定这个线程在终止时是否可以被结合)
    pthread_attr_setdetachstate(&m_Pthread_attr_t, PTHREAD_CREATE_DETACHED);
    //pthread_create(&m_PThread, &m_Pthread_attr_t, &initRun, NULL);
    turnFlag();
    cout << "thread  flag" << m_Flag << endl;
    //pthread_detach(pThread);
}