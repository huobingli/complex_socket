/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   threadPool.cpp
 * Author: 炳雳
 * 
 * Created on 2016年12月8日, 下午7:56
 */

#include "threadPool.h"

ThreadPool::ThreadPool(int iThreadNum) {
    m_ThreadNum = iThreadNum;
    m_ThreadPool = new Thread[iThreadNum];
    for (int i = 0; i < iThreadNum; i++) {
        m_ThreadPool[i].initThread();
    }
}

ThreadPool::ThreadPool(const ThreadPool& orig) {

}

ThreadPool::~ThreadPool() {
    delete [] m_ThreadPool;
}

/*
void allocThread(void(*callback)(void *arg)) {
    cout << "构建工作队列元素对象" << endl;
    runner *newCallBack = (runner *) malloc(sizeof (runner));
    newCallBack->callback = callback;
    newCallBack->next = NULL;

    //newCallBack->arg = arg;
    pthread_mutex_lock(&mutex);
    if (runnerHead != NULL) {
        runnerTail->next = newCallBack;
        runnerTail = newCallBack;
    } else {
        runnerHead = newCallBack;
        runnerTail = newCallBack;
    }
    if (sendTable->getNodeNum() != 0 || recvTable->getNodeNum() != 0) {
        //cout<<(runnerHead != NULL)<<endl;
        cout << "allocThread  发送信号" << endl;
        pthread_cond_signal(&cond);
    }
    pthread_mutex_unlock(&mutex);
}*/