/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   onlineDevice.cpp
 * Author: 炳雳
 * 
 * Created on 2016年12月8日, 下午7:55
 */

#include "onlineDevice.h"

onlineDevice::onlineDevice(int iNum) {
    m_TotalNum = iNum;
    m_NodeNum = 0;
    m_OnLineTable = (struct _onlineDevice *)malloc(sizeof(_onlineDevice) * iNum);
    memset(m_OnLineTable, 0, sizeof(_onlineDevice) * iNum);
}

onlineDevice::onlineDevice(const onlineDevice& orig) {
    free (m_OnLineTable);
}

onlineDevice::~onlineDevice() {
}

bool onlineDevice::insertDevice(_onlineDevice *pDevice) {
    if (full()) { return false; }
    else {
	for (int i = 0; i < m_NodeNum; i++){
            //如果两个设备相同, 更新设备信息，将插入标志置为true
	    if (m_OnLineTable[i].iDeviceID == pDevice->iDeviceID) {
                memcpy(&m_OnLineTable[i], pDevice, sizeof(_onlineDevice));
		return true;
	    }
	}
	//没有在for中找到相同数据， 插入新数据到数组
	memcpy(&m_OnLineTable[m_NodeNum], pDevice, sizeof(_onlineDevice));
	m_NodeNum++;
	return true;
    }
}

void onlineDevice::transSQLQuery(int index, char *pSqlBuffer) {
    sprintf(pSqlBuffer, 
            "update device(temp, hum, longitude, latitude, deviceStatus, dateTime) values (%d, %d, %.6f, %.6f, %d, %d) where deviceID = %d", 
            m_OnLineTable[index].iTemperature, m_OnLineTable[index].iHumidity, m_OnLineTable[index].longitude,
            m_OnLineTable[index].latitude, m_OnLineTable[index].iSSMStatus, m_OnLineTable[index].iLastUpdateTime,
            m_OnLineTable[index].iDeviceID);
}

//设置设备为离线状态
//在线状态为false , 写入数据库标志位true
void onlineDevice::setDeviceOffLine(int iIndex) {
    m_OnLineTable[iIndex].bIsOnLine = false;
    m_OnLineTable[iIndex].bIsSave = true;
}

//插入所有数据到数据库
void onlineDevice::saveAllDeviceInfo() {
    for (int i = 0; i < m_NodeNum; i++){
	m_OnLineTable[i].bIsSave = true;
    }
}