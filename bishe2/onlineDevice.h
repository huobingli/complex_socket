/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   onlineDevice.h
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午7:55
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

using namespace std;

#ifndef _ONLINEDEVICE_
#define _ONLINEDEVICE_
struct _onlineDevice {
    int iSt;
    struct sockaddr_in sSockaddr;
    int iLoginTime;                 //unix timeStamp 10位
    int iLastUpdateTime;            //unix timeStamp 10位
    int iDeviceID;                  //在线设备ID
    bool bIsOnLine;                 //在线标志位
    bool bIsSave;                   //是否保存位
    char iSSMStatus;                //设备状态
    int iTemperature;               //设备温度
    int iHumidity;                  //设备湿度
    double longitude;               //经度
    double latitude;                //纬度
};
#endif

#ifndef ONLINEDEVICE_H
#define ONLINEDEVICE_H

class OnlineDevice {
public:
    OnlineDevice(int iNum);
    OnlineDevice(const OnlineDevice& orig);
    virtual ~OnlineDevice();
    int getOnLineNum() { return m_NodeNum; }
    bool insertDevice(_onlineDevice *pDevice);
    void transSQLQuery(int index, char *pSqlBuffer);
    void setDeviceOffLine(int iIndex);
    void saveAllDeviceInfo();
    int scanSameDevice(int iSt);
    
private:
    bool empty() {return m_NodeNum == 0;}
    bool full() {return m_NodeNum == m_TotalNum;}
private:
    _onlineDevice *m_OnLineTable;
    int m_NodeNum;
    int m_TotalNum;
};

#endif /* ONLINEDEVICE_H */

