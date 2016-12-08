/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   threadFuntion.h
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午8:22
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
#include <stdio.h>

#include "structClass.h"
using namespace std;

#ifndef THREADFUNTION_H
#define THREADFUNTION_H
static void *epollRecv(void *arg) {

    cout<<"接受线程启动"<<endl;
    
    //canshu
    _recv_param *balabala = (struct _recv_param *) arg;
    serverSocket *serverSt = (*balabala).serverSt;
    epoll *serverEpoll = (*balabala).serverEpoll;
    cacheTable *recvTable = (*balabala).pRecvTable;
    //cout<<"epollRecv"<<endl;
    int listen_st = serverSt->getst();
    
    struct epoll_event ev;
    ev.data.fd = listen_st;
    
    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
    
    serverEpoll->addEpoll(listen_st, ev);
    
    int st = 0;
    while(1) {
        int nfds = serverEpoll->waitEpoll(-1);
        //cout<<"nfds : "<<nfds<<endl;
        if(nfds == -1) {
            cout<<"epoll wait failed"<<strerror(errno);
            break;
        }
        
        int i;
        int fd;
        
        for(i = 0; i<nfds; i++) {
            fd = serverEpoll->getfd(i);
            if(fd < 0) {
                continue;
            }
            
            if(fd == listen_st) {
                cout<<"监测到一个socket链接"<<endl;
                st = serverSt->acceptSocket(listen_st);
                
                //cout<<"st = "<<st<<"; listen_st = "<<listen_st<<endl;
                if(st > 0) {
                    
                    setNoBlocking(st);
                    
                    ev.data.fd = st;
                    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
                    serverEpoll->addEpoll(st, ev);
                    continue;
                }
            }
            
            
            __uint32_t events = serverEpoll->getEvent(i);
            st = serverEpoll->getfd(i);
            
            //socket get data
            if(events & EPOLLIN) {
                cout<<"recv from : " <<st<<endl;
                char buffer[MAXSIZE];
                memset(&buffer, 0, sizeof(buffer));
                serverSt->recvSocket(st, buffer);
                
                if(strlen(buffer) <= 0) {
                    serverSt->sendSocket(st);
                    close(st);
                }
                if(strlen(buffer) > 0) {
                    cout<<"recv buffer : "<<buffer <<endl;
                    
                }
            }
            //socket error
            if(events & EPOLLERR) {
                st = serverSt->acceptSocket(listen_st);
                close(st);
            }
            //socket unlinked
            if(events & EPOLLHUP) {
                st = serverSt->acceptSocket(listen_st);
                close(st);
            }
        }
    }    
}

#endif /* THREADFUNTION_H */

