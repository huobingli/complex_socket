#pragma once
#include "Cyclequeue.h"


/**
* ѭ�������࣬������Ϣ���У���Ž��ջ��ߴ���֮�������
* ����һ�����Ա��ṹ���飩���ܸ����Լ���ǰ���и���
* �ṩCRUD������
*/
struct queuenode{
	int  iSt;				//socket�׽���
	char cIPBuffer[20];		//���յ�IP
	char cOperate;			//��������
	char cNodeBuffer[128];	//����buffer
	int  iNodeBufferLength;	//����buffer����
};

class CQueueControl
{
private:
	//���б�
	queuenode m_QueueTable[20];
	
	//���в���
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
		//������
		if (fullQueue()) {
			return false;
		}
		else {
			//�������Ϊ��
			if (emptyQueue()) {
				//��������
				memcpy(&m_QueueTable[m_NodeNum], pQueueNode, sizeof(queuenode));
				++m_NodeNum;
				return true;
			}
			else {
				//��������
				memcpy(&m_QueueTable[m_NodeNum], pQueueNode, sizeof(queuenode));
				++m_NodeNum;
				return true;
			}
		}
	}

	bool deleteQueueNode(int iNodeNum) {

	}

	//���������е�
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

	//����ά���������������м䲻������Ч����
	void defendQueue(int index) {
		if (index == m_NodeNum)
		{
			//ֱ���������һ��Ϊ0
			memset(&m_QueueTable[index], 0, sizeof(queuenode));
		}
		else {
			int tempNum = m_NodeNum - 1;
			for (int i = index; i < m_NodeNum; i++) {
				//ά��Ԫ����ǰ����
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

