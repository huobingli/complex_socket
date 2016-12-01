#pragma once
#include "Cyclequeue.h"


/**
* 循环队列类，用作消息队列，存放接收或者处理之后的数据
* 包含一个线性表（结构数组），总个数以及当前表中个数
* 提供CRUD操作，
*/
struct queuenode{
	int  iSt;				//socket套接字
	char cIPBuffer[20];		//接收的IP
	char cOperate;			//操作符号
	char cNodeBuffer[128];	//操作buffer
	int  iNodeBufferLength;	//操作buffer长度
};

class CQueueControl
{
private:
	//队列表
	queuenode m_QueueTable[20];
	
	//队列参数
	int m_NodeNum;
	int m_TotalNum;
	int m_GetArray[10];
private:
	bool fullQueue() {
		return m_NodeNum == m_TotalNum;
	}
	bool emptyQueue() {
		return m_NodeNum == 0;
	}

public:
	CQueueControl(int iNodeNum) {
		m_NodeNum = 0;
		m_TotalNum = iNodeNum;
		memset(m_GetArray, 0, sizeof(m_GetArray));

		memset(m_QueueTable, 0, sizeof(queuenode) * 20);
	}
	~CQueueControl();

	bool insertQueueNode(queuenode *pQueueNode) {
		//队列满
		if (fullQueue()) {
			return false;
		}
		else {
			//如果队列为空
			if (emptyQueue()) {
				//拷贝数据
				memcpy(&m_QueueTable[m_NodeNum], pQueueNode, sizeof(queuenode));
				++m_NodeNum;
				return true;
			}
			else {
				//拷贝数据
				memcpy(&m_QueueTable[m_NodeNum], pQueueNode, sizeof(queuenode));
				++m_NodeNum;
				return true;
			}
		}
	}

	bool deleteQueueNode(int iNodeNum) {

	}

	//搜索到所有的
	int scanRecvQueueNode(char cOperate) {
		int iNum = 0;
		for (int i = 0; i < m_NodeNum; i++) {		
			if (m_QueueTable[i].cOperate == cOperate){
				m_GetArray[iNum] = i;
				++iNum;
			}
		}
		return iNum;
	}

	void getQueueNode(int iIndex, queuenode *pQueueNode) {		
		memcpy(pQueueNode, &m_QueueTable[iIndex], sizeof(queuenode));
		defendQueue(iIndex);
		--m_NodeNum;
	}

	//用来维护队列完整，是中间不出现无效数据
	void defendQueue(int index) {
		if (index == m_NodeNum)
		{
			//直接设置最后一个为0
			memset(&m_QueueTable[index], 0, sizeof(queuenode));
		}
		else {
			int tempNum = m_NodeNum - 1;
			for (int i = index; i < m_NodeNum; i++) {
				//维护元素向前推移
				if (i == tempNum)
					memset(&m_QueueTable[i], 0, sizeof(queuenode));
				else
					memcpy(&m_QueueTable[i], &m_QueueTable[i + 1], sizeof(queuenode));
			}
		}
	}

	int *getArray() {
		return m_GetArray;
	}
	void resetArray() {
		memset(m_GetArray, 0, sizeof(m_GetArray));
	}
};

