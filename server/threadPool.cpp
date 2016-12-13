#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "queuePool.cpp"
#include "serverSocket.cpp"
#include "epoll.cpp"
#include "onlineDevice.cpp"


using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

cacheLinkTable *sendTable;
cacheLinkTable *recvTable;



struct serverRecv {
	serverSocket *serverSt;
	epoll *serverEpoll;
	cacheLinkTable *pLinkTable;
	onlineDevice *onlineDeviceTable;
};

struct serverSend {
	cacheLinkTable *pLinkTable;
};

struct serverAnal {
	cacheLinkTable *pSendTable;
	cacheLinkTable *pRecvTable;
	onlineDevice *onlineDeviceTable;
};

struct runner
{
    void (*callback)(void *arg);//回调函数指针
    void *arg;                //回调函数参数
    struct runner *next;//next runner
};

//runner *newCallBack;
struct serverSend *Send;

runner *runnerHead;
runner *runnerTail;


#ifndef _THREAD_CPP
#define _THREAD_CPP

class thread{
private:
	pthread_t pThread;
	pthread_attr_t attr;
	int iFlag;

public:
	thread() {
		iFlag = 0;
	}

	~thread() {

	}

	static void *initRun(void *arg) {

		while(1) {
			pthread_mutex_lock(&mutex);
			cout<<"hello "<<endl;
			// while(sendTable->getNodeNum() == 0 || recvTable->getNodeNum() != 0) {

			// 	cout<<"fuck linux"<<endl;
			// 	pthread_cond_wait(&cond, &mutex);
			// 	sleep(5);
			// }
			while(runnerTail == NULL) {
				pthread_cond_wait(&cond, &mutex);
			}
			pthread_mutex_unlock(&mutex);
			//cout<<"101010"<<endl;

			serverAnal *analyze = (serverAnal *)malloc(sizeof(serverAnal));
			analyze->pSendTable = sendTable;
			analyze->pRecvTable = recvTable;
			// cout<<analyze->pSendTable->getNodeNum()<<endl;
			runnerTail->arg = analyze;
			(runnerTail->callback)(runnerTail->arg);
			free(runnerTail);
			//(newCallBack->callback)(newCallBack->arg);

			sleep(10);
		}
	}

	//init pThread
	void initThread() {
		//cout<<"3333"<<endl;
		//初始化线程的属性
		pthread_attr_init(&attr);
		//设置脱离状态的属性(决定这个线程在终止时是否可以被结合)
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		pthread_create(&pThread, &attr, &initRun, NULL);
		turnFlag();
		cout<<"thread  flag"<<iFlag<<endl;
		//pthread_detach(pThread);
	}

	int getFlag() {
		return iFlag;
	}

	void turnFlag() {
		iFlag = (iFlag == 0) ? 1 : 0;
	}
};
#endif

#ifndef _THREADPOOL_CPP
#define _THREADPOOL_CPP

class threadPool {
private:
	thread *pthreadPool;
	int iThreadNum;
public:

	int getThreadNum() {
		return iThreadNum;
	}

  //gouzao
	threadPool(int threadNum, cacheLinkTable *pSendTable, cacheLinkTable *pRecvTable, onlineDevice *pOnlineTable) {
		//thread queue linkTable

		sendTable = pSendTable;
		recvTable = pRecvTable;
		onlineTable = pOnlineTable;

		cout<<"const threadPool"<<sendTable->getNodeNum()<<endl;
		cout<<"const threadPool"<<recvTable->getNodeNum()<<endl;
		cout<<"const threadPool"<<pOnlineTable->getOnLineNum()<<endl;
		runnerHead = NULL;
		runnerTail = NULL;
		//thread pool threads
		iThreadNum = threadNum;


		pthreadPool = new thread[iThreadNum];
		for(int i = 0; i<iThreadNum; i++) {
			cout<<pthreadPool[i].getFlag()<<endl;
		}
		for(int i = 0; i < iThreadNum; i++) {
			pthreadPool[i].initThread();
		}
	}
	~threadPool() {

	}

	void allocThread(void(*callback)(void *arg)) {
		cout<<"构建工作队列元素对象"<<endl;
		runner *newCallBack =  (runner *)malloc(sizeof(runner));
		newCallBack->callback = callback;
		newCallBack->next = NULL;

		//newCallBack->arg = arg;
		pthread_mutex_lock(&mutex);
		if(runnerHead != NULL)
		{
		     runnerTail->next = newCallBack;
		     runnerTail = newCallBack;
		}
		else
		{
		     runnerHead = newCallBack;
		     runnerTail = newCallBack;
		}
		if(sendTable->getNodeNum() != 0 || recvTable->getNodeNum() != 0) {
			pthread_cond_signal(&cond);

			cout<<"发送启动发送信号"<<endl;
		}
		pthread_mutex_unlock(&mutex);
	}

  //jieshou fenxi xiancheng
	void allocAnalyzeThread(void(*callback)(void *arg)) {

	}


	void recoverThread() {

	}

	void setSendTable(cacheLinkTable *linkTable) {
		sendTable = linkTable;
	}

	void setRecvTable(cacheLinkTable *linkTable) {
		recvTable = linkTable;
	}

	struct runner *getWorkQueue() {
		return runnerHead;
	}
	thread *getThread() {
		return pthreadPool;
	}

protected:
	int searchPool() {
		for(int i = 0; i < iThreadNum; i++) {
			if(pthreadPool[i].getFlag() == 0)
			{
				return i;
			}
			else
				return 0;
		}
	}

};
#endif
