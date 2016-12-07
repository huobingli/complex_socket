
//********************************************************
//
//       FileName:      onlineDevice.cpp
//
//       Author:         
//       Description:    
//       Create:        2016-12-06 20:35:50
//       Last Modified: 2016-12-06 20:35:50
//********************************************************


#include <iostream>
using namespace std;

#ifndef _ONLINEDEVICE_CPP
#define _ONLINEDEVICE_CPP
struct onlineArray{
  int iSt;
  struct sockaddr_in sOnlineInfo;
  bool bIsOnLine;
  bool bIsNeedSave;
};


class onlineDevice {
private:
  onlineArray *m_onLine;
  int m_onLineNum;
  int m_TotalNum;
private:
  bool empty() { return m_onLineNum == 0;}
  bool full() { return m_onLineNum == m_TotalNum; }
  bool scanSame(int iSt) {
  	if(empty()) return false;
  	else {
//		cout<<222<<endl;
  		for(int i = 0; i < m_onLineNum; i++) {
  			if(m_onLine[i].iSt == iSt) {
  				return true;
  			}
  		}
		return false;
  	}
  }
public:
  onlineDevice(int iNum) {
    m_onLine = (struct onlineArray*)malloc(sizeof(onlineArray) * iNum);
    memset(m_onLine, 0, sizeof(onlineArray) * iNum);
    m_onLineNum = 0;
    m_TotalNum = iNum;
  }
  
  ~onlineDevice() { //free *m_onLine;
  }

  int getOnLineNum() { return m_onLineNum; }
  void insertArray(int iSt, struct sockaddr_in *pSockAddr) {
    cout<<iSt<<endl;
    if(full()) { 
	cout<<"manle manle manle "<<endl;
	return; 
    }
    else {
    	if(scanSame(iSt)) return;
      	else {
//		cout<<"1111"<<endl;
	      	//插入到在线列表
	      	m_onLine[m_onLineNum].iSt = iSt;
	      	memcpy(&m_onLine[m_onLineNum].sOnlineInfo, pSockAddr, sizeof(struct sockaddr_in));
		cout<<"saved ip "<<inet_ntoa(m_onLine[m_onLineNum].sOnlineInfo.sin_addr)<<endl;
	      	
		m_onLine[m_onLineNum].bIsOnLine = true;
	      	m_onLine[m_onLineNum].bIsNeedSave = true;
	      	m_onLineNum++;
      	}
    }
  }

  void clearArray() { 
    if(empty()) { return; }
    else { 
      
    }
  }

  void searchNode(int iSt) {
  	for(int i = 0; i < m_onLineNum; i++) {
  		if(m_onLine[i].iSt == iSt)
  			cout<<inet_ntoa(m_onLine[i].sOnlineInfo.sin_addr)<<endl;
  	}
  }
  

};

#endif
