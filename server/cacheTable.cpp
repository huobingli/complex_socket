
//********************************************************
//
//       FileName:      cacheTable.cpp
//
//       Author:         
//       Description:    
//       Create:        2016-12-07 13:17:35
//       Last Modified: 2016-12-07 13:17:35
//********************************************************

<<<<<<< HEAD

=======
#include <netinet/in.h>
#include <string.h>
>>>>>>> 5ef238650f41a5baca738e1df2f7ed65ee074aac
#ifndef _CACHETABLE_CPP_
#define _CACHETABLE_CPP_

struct cacheNode {
	int iSt;
	struct sockaddr_in sSockAddr;
	char cOperate;
	char cNodeBuffer[256];
	char iNodeBufferLength;
};

class cacheTable{
private:
	cacheNode m_QueueTable[20];
	int m_NodeNum;
	int m_TotalNum;
	int m_GetArray[10];
private:
	bool fullQueue() { return m_NodeNum == m_TotalNum; }
	bool emptyQueue() { return m_NodeNum == 0; }
public:
<<<<<<< HEAD
	CQueueControl(int iNodeNum) {
=======
	cacheTable(int iNodeNum) {
>>>>>>> 5ef238650f41a5baca738e1df2f7ed65ee074aac
		m_NodeNum = 0;
		m_TotalNum = iNodeNum;
		memset(m_QueueTable, 0, sizeof(cacheNode) * 20);
	}
<<<<<<< HEAD
	~CQueueControl() {}
=======
	~cacheTable() {}
>>>>>>> 5ef238650f41a5baca738e1df2f7ed65ee074aac
	bool insertQueueNode(cacheNode *pQueueNode) {
		if(fullQueue()) { return false; }
		else {	
			memcpy(&m_QueueTable[m_NodeNum], pQueueNode, sizeof(cacheNode));
			++m_NodeNum;
			return true;
		}
	}
	int scanRecvQueueNode(char cOperate) {
		int iNum = 0;
		for(int i = 0; i < m_NodeNum; i++) {
			if(m_QueueTable[i].cOperate == cOperate) {
				m_GetArray[iNum] = i;
				++iNum;
			}
		}
		return iNum;
	}
	void getQueueNode(int iIndex, cacheNode *pQueueNode) {		
		memcpy(pQueueNode, &m_QueueTable[iIndex], sizeof(cacheNode));
		defendQueue(iIndex);
		--m_NodeNum;
	}
	void defendQueue(int index) {
		if (index == m_NodeNum)
		{
			//直接设置最后一个为0
			memset(&m_QueueTable[index], 0, sizeof(cacheNode));
		}
		else {
			int tempNum = m_NodeNum - 1;
			for (int i = index; i < m_NodeNum; i++) {
				//维护元素向前推移
				if (i == tempNum)
					memset(&m_QueueTable[i], 0, sizeof(cacheNode));
				else
					memcpy(&m_QueueTable[i], &m_QueueTable[i + 1], sizeof(cacheNode));
			}
		}
	}
	int *getArray() {
		return m_GetArray;
	}
	void resetArray() {
		memset(m_GetArray, 0, sizeof(m_GetArray));
	}
<<<<<<< HEAD
=======
	int getNodeNum() { return m_NodeNum; }
>>>>>>> 5ef238650f41a5baca738e1df2f7ed65ee074aac
};

#endif
