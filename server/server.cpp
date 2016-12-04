#include "threadControl.cpp"
using namespace std;


struct serverRecv recvOprate;
struct serverSend sendOprate;
struct serverAnal doubleOperate;

void setNoBlocking(int st)
{
	int opts = fcntl(st, F_GETFL);
	if(opts <0)
	{
		cout<<"fcntl failed "<< strerror(errno);
	}

	opts = opts | O_NONBLOCK; // 或运算
	if(fcntl(st, F_SETFL, opts) < 0)
	{
		cout<<"fcntl failed "<< strerror(errno);
	}

	cout<<"set success"<<endl;
}


static void *epollRecv(void *arg) {

	cout<<"接受线程启动"<<endl;

	//canshu
	serverRecv *balabala = (struct serverRecv *) arg;
	serverSocket *serverSt = (*balabala).serverSt;
	epoll *serverEpoll = (*balabala).serverEpoll;
	cacheLinkTable *recvTable = (*balabala).pLinkTable;
//	cout<<"epollRecv"<<endl;
	int listen_st = serverSt->getst();

	struct epoll_event ev;
	ev.data.fd = listen_st;

	ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;

	serverEpoll->addEpoll(listen_st, ev);

	int st = 0;
	while(1) {
		//获得有事件socket
		int nfds = serverEpoll->waitEpoll(-1);
		cout<<"nfds : "<<nfds<<endl;
		if(nfds == -1) {
			cout<<"epoll wait failed"<<strerror(errno);
			breadk;
		}

		int i;
		int fd;

		for(i = 0; i<nfds; i++) {
      //获得一个文件描述符
			fd = serverEpoll->getfd(i);
			if(fd < 0) {
				continue;
			}
	
			if(fd == listen_st) {
        //得到客户端socket
        st = serverSt->acceptSocket(listen_st);
				cout<<"st = "<<st<<"; listen_st = "<<listen_st<<endl;

				if(st > 0) {
					setNoBlocking(st);
					ev.data.fd = st;
					ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
					//将客户端的socket加入epoll池
					serverEpoll->addEpoll(st, ev);
					continue;
				}
			}

			__uint32_t events = serverEpoll->getEvent(i);
			st = serverEpoll->getfd(i);

			//socket get data
			if(events & EPOLLIN) {
				cout<<"recv from : " <<st<<endl;
				char buffer[MAXSIZE];
				memset(&buffer, 0, sizeof(buffer));
				serverSt->recvSocket(st, buffer);

				if(strlen(buffer) <= 0) {
					serverSt->sendSocket(st);
					close(st);
				}
				if(strlen(buffer) > 0) {
					cout<<"recv buffer : "<<buffer <<endl;
					cacheLinkNode *cacheNode = new cacheLinkNode();
					cacheNode->setst(st);
					cacheNode->setbuffer(buffer);

					pthread_mutex_lock(&RecvMutex);
					cout<<"接收队列已经加锁，正在写入数据"<<endl;
					recvTable->insertNode(cacheNode);
					pthread_mutex_unlock(&RecvMutex);
					cout<<"接收队列已经解锁，等待中"<<endl;

					cout<<"end analyze recvTable Node NUM  "<<recvTable->getNodeNum()<<endl;
				}
			}
			//socket error
			if(events & EPOLLERR) {
				st = serverSt->acceptSocket(listen_st);
				close(st);
			}
			//socket unlinked
			if(events & EPOLLHUP) {
				st = serverSt->acceptSocket(listen_st);
				close(st);
			}
		}
	}
}


int main () {
	// new send recv queue
	queuePool * pQueuePool = new queuePool();

	// init server listen socket

	recvOprate.serverSt = new serverSocket(10000);
	recvOprate.serverSt->createServerSocket();

	int listen_st = recvOprate.serverSt->getst();
	if(listen_st == 0)
		return 0;
	setNoBlocking(listen_st);

	// init epoll
	recvOprate.serverEpoll = new epoll(100);
	recvOprate.serverEpoll->createEpoll();

	//recv queue and send queue
	recvOprate.pLinkTable = pQueuePool->getRecvTable();
	sendOprate.pLinkTable = pQueuePool->getSendTable();
	doubleOperate.pRecvTable = recvOprate.pLinkTable;
	doubleOperate.pSendTable = sendOprate.pLinkTable;

	pthread_t thrd1, thrd2, thrd3, thrd4;
	pthread_create(&thrd1, NULL, epollRecv, &recvOprate);
	// pthread_create(&thrd3, NULL, epollAnalyze, &doubleOperate);
	// pthread_create(&thrd2, NULL, epollSend, &sendOprate);

	threadControl *pthreadControl = new threadControl(3,sendOprate.pLinkTable, recvOprate.pLinkTable);
	classpoint *threadPool = (struct classpoint *)malloc(sizeof(classpoint))	;
	threadPool->pThreadPool = pthreadControl->getThreadPool();
	pthread_t thrdHeart;
	pthread_create(&thrdHeart, NULL, threadControl::heartBreath, threadPool);

while(1) {}
	return 0;
}
