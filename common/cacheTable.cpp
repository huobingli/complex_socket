
//********************************************************
//
//       FileName:      cacheTable.cpp
//
//       Author:  huobingli - huobingli@outlook.com
//       Description:    
//       Create: 2016-12-01  18:47:51
//       Last Modified: 2016-12-01 18:47:51
//********************************************************
// 
#include <iostream>
using namespace std;


#ifndef _CACHETABLE_CPP
#define _CACHETABLE_CPP
struct  cacheNode {
	int 	iSt;
	char	cIPBuffer[16];
	int	iIPLength;
	char	cPortBuffer[6];
	int 	iPortLength;
	char 	cNodeBuffer[128];
	int 	iNodeBufferLength;

	//mq
	char	cOperate;
};

class cacheTable{
private:
	cacheNode m_CacheTable[20];
	int 	  m_NodeNum;
	int 	  m_TotalNum;
	int 	  m_GetArray[20];

	bool fullTable() {return m_NodeNum == m_TotalNum;}
	bool emptyTable() {return m_NodeNum == 0;}
public:
	cacheTable(int iNodeNum) {
		m_NodeNum = 0;
		m_TotalNum = iNodeNum;
		memset(m_GetArray, 0, sizeof(m_GetArray));
		memset(m_CacheTable, 0, sizeof(cacheNode) * iNodeNum);
	}
	~cacheTable() {
		delete [] m_CacheTable;
	}
	
	bool insertCacheNode(cacheNode *pCacheNode) {
		if(fullTable()) return false;
		else {
			memcpy(&m_CacheTable[m_NodeNum], pCacheNode, sizeof(CacheNode));
			++m_NodeNum;
			return true;
		}
	}
	
	int scanTableNodeNum(char cOperate) {
		int iNum = 0;
		for(int i = 0; i< m_NodeNum;i++) {
			if(m_CacheTable[i].cOperate == cOperate) {
				m_GetArray[iNum] == i;
				++iNum;
			}
		}
		return iNum;
	}

	void getCacheNode(int iIndex, cacheNode *pCacheNode) {
		memcpy(pCacheNode, &m_QueueTable[iIndex], sizeof(cacheNode));
		defendTable(iIndex);
		--m_NodeNum;
	}

	void defendQueue(int iIndex) {
		//如果需要维护最后一个，直接将最后一个重置
		if(index == m_NodeNum) {
			memset(m_CacheTable[iIndex], 0, sizeof(cacheNode));
		}
		else {
			int tempNum = m_NodeNum - 1;
			for(int i = index; i < m_NodeNum; i++) {
				if(i == tempNum) 
					memset(&m_CacheTable[i], 0, sizeof(cacheNode));
				else
					memset(&m_CacheTable[i], &m_CacheTable[i + 1], sizeof(cacheNode));
			}
		}
	}

	int *getArray() { return m_GetArray; }
	void resetArray() { memset(m_GetArray, 0, sizeof(m_GetArray)); }
};

#endif
