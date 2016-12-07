#include <pthread.h>
#include "threadPool.cpp"
#include "serverAnalyze.cpp"
#include "cacheTable.cpp"
using namespace std;

//
pthread_mutex_t RecvMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t SendMutex = PTHREAD_MUTEX_INITIALIZER;
struct classpoint {
	threadPool *pThreadPool;
};

static void epollSend(void *arg) {
	cout<<"发送线程启动"<<endl;
	struct serverAnal *balabala = (struct serverAnal*)arg;
	cacheTable *psendTable = (*balabala).pSendTable;


	while(1){
		sleep(5);
		cout<<"send sendLinkTable Node NUM  "<<psendTable->getNodeNum()<<endl;
		if(psendTable->getNodeNum() > 0)
		{
/*
			cout<<"有"<<psendTable->getNodeNum()<<"条要发送"<<endl;

			pthread_mutex_lock(&SendMutex);
			cout<<"发送队列已经加锁"<<endl;
			cacheLinkNode *tempNode = psendTable->getEndNode();
			pthread_mutex_unlock(&SendMutex);
			cout<<"发送队列已经解锁"<<endl;

			int st = tempNode->getst();
			char *haha="服务器准备发送\t";
			send(st, haha, strlen(haha), 0);
			char buffer[MAXSIZE];
			memset(&buffer, 0, MAXSIZE);

			tempNode->getbuffer(buffer);
			send(st, buffer, strlen(buffer), 0);

			cout<<"已经向"<<st<<"发送了"<<buffer<<endl;*/
		}
	}
}

/***********************************************************************/
static void epollAnalyze(void *arg) {
	cout<<"处理线程启动"<<endl;
	//struct serverAnalyze *balabala = (struct serverAnalyze *)arg;
	//cacheTable *sendTable = (*balabala).pSendTable;
	//cacheTable *recvTable = (*balabala).pRecvTable;
	//onlineDevice *pOnlineDevice = (*balabala).onlineDeviceTable;

	char buffer[MAXSIZE];
	memset(&buffer, 0, sizeof(buffer));
	serverAnalyze *pServerAnalyze = new serverAnalyze();
	while(1){

		//cout<<"epoll analyze sendLinkTable Node NUM  "<<sendTable->getNodeNum()<<endl;
		//cout<<"epoll analyze recvLinkTable Node NUM  "<<recvTable->getNodeNum()<<endl;

/*		if(recvTable->getNodeNum() != 0) {

			pthread_mutex_lock(&RecvMutex);
			cout<<"正在处理一条信息"<<endl;
			struct cacheNode tempCacheNode;
			pthread_mutex_unlock(&RecvMutex);

			//cacheLinkNode *insertSendTableNode = new cacheLinkNode();

			//------------------------------
			//messageBuffer *message = new messageBuffer();

			tempCacheNode

			if(buffer[0] == '1')
				pOnlineDevice->searchNode();
			//set buffer
			//pServerAnalyze->setBuffer(buffer);
			//pServerAnalyze->judgeBuffer();
			//-------------------------------

			//tempLinkNode->copyLinkNode(insertSendTableNode);

			

			cout<<"信息处理完毕"<<endl;
			//break;

			//pthread_mutex_lock(&SendMutex);
			//cout<<"正在加入发送队列"<<endl;
			//sendTable->insertNode(insertSendTableNode);
			//pthread_mutex_unlock(&SendMutex);
			//cout<<"添加完成"<<endl;

		}

		sleep(5);
		//cout<<"epoll analyze end analyze sendLinkTable Node NUM  "<<sendTable->getNodeNum()<<endl;
		//cout<<"epoll analyze end analyze recvLinkTable Node NUM  "<<recvTable->getNodeNum()<<endl;*/
	}
	cout<<"处理线程退出"<<endl;
}
/***********************************************************************/

#ifndef _THREADCONTROL_CPP
#define _THREADCONTROL_CPP

class threadControl {
private:
	threadPool *pThreadPool;
	int iThreadNum;
	int shutdown;
public:
	threadControl(int threadNum, cacheTable *pSendTable, cacheTable *pRecvTable, onlineDevice *pOnlineDevice) {
		iThreadNum = threadNum;
		//cout<<"000"<<endl;
		pThreadPool = new threadPool(iThreadNum, pSendTable, pRecvTable, pOnlineDevice);
		//cout<<"999"<<endl;
		shutdown = 1;
	}

	~threadControl() {}

	// return threadPool status
	int getStatus() {
		return shutdown;
	}

	threadPool *getThreadPool() {
		return pThreadPool;
	}

	static void *heartBreath(void *arg) {

		classpoint *newPoint = (classpoint*) arg;

		//test
		threadPool *threadPool = newPoint->pThreadPool;

		while(1) {
			cout<<"threadNum"<<threadPool->getThreadNum()<<endl;
			sleep(6);
			cout<<"sendTableNodeNum"<<sendTable->getNodeNum()<<endl;
			cout<<"recvTableNodeNum"<<recvTable->getNodeNum()<<endl;
			cout<<"heartBreath"<<endl;
			if(sendTable->getNodeNum() != 0) {
				newPoint->pThreadPool->allocThread(epollSend);
			}

			if(recvTable->getNodeNum() != 0) {
				cout<<"应该启动分析线程"<<endl;
				newPoint->pThreadPool->allocThread(epollAnalyze);
			}

			cout<<"show thread flag info"<<endl;
			for(int  i = 0; i  <  3; i++){
				//cout<<threadPool[i]->getThread()<<endl;
			}

		}
	}
};
#endif
