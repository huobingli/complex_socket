/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Epoll.cpp
 * Author: 炳雳
 * 
 * Created on 2016年12月8日, 下午7:56
 */

#include "epoll.h"

Epoll::Epoll(int iNum) {
    iMaxLink = iNum;
    pEvents = NULL;
    iLinkNum = 0;
}

Epoll::Epoll(const Epoll& orig) {
}

Epoll::~Epoll() {
}

int Epoll::createEpoll() {
    if (iMaxLink < 0)
        cout << "error, iMaxLink cannot xiaoyu 0";
    iEpfd = epoll_create(iMaxLink);
    pEvents = new epoll_event[iMaxLink + 1];
}

//epoll wait events triger
int Epoll::waitEpoll(int second) {
    return epoll_wait(iEpfd, pEvents, iMaxLink, second);
}

//zhuce event into epoll
void Epoll::addEpoll(int st, struct epoll_event ev) {
    epoll_ctl(iEpfd, EPOLL_CTL_ADD, st, &ev);
}

//delete event from epoll
void Epoll::deleteEpoll(int st, struct epoll_event ev) {
    epoll_ctl(iEpfd, EPOLL_CTL_DEL, st, &ev);
}

//get events fd
__uint32_t Epoll::getEvent(int i) {
    return pEvents[i].events;
}

int Epoll::getfd(int i) {
    return pEvents[i].data.fd;
}

void Epoll::get()
{
    cout << "iMaxLink" << iMaxLink << "iLinkNum" << iLinkNum << endl;
}


