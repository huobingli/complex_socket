/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Epoll.h
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午7:56
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

using namespace std;
#ifndef EPOLL_H
#define EPOLL_H

class Epoll {
private:
    int iMaxLink;// max link num
    int iEpfd; //
    struct epoll_event *pEvents;
    int iLinkNum;//linked num
public:
    Epoll(int iNum);
    Epoll(const Epoll& orig);
    virtual ~Epoll();
    
    // create Epoll
    int createEpoll();

    //Epoll wait events triger
    int waitEpoll(int second);

    //zhuce event into Epoll
    void addEpoll(int st, struct epoll_event ev);

    //delete event from Epoll
    void deleteEpoll(int st, struct epoll_event ev);

    //get events fd
    __uint32_t getEvent(int i);

    int getfd(int i);

    void get();

};

#endif /* EPOLL_H */

