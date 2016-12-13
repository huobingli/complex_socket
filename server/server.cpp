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

  //获取结构体参数
  serverRecv *balabala = (struct serverRecv *) arg;
  serverSocket *serverSt = (*balabala).serverSt;
  epoll *serverEpoll = (*balabala).serverEpoll;
  cacheLinkTable *recvTable = (*balabala).pLinkTable;
  onlineDevice *onlineDeviceTable = (*balabala).onlineDeviceTable;
  //得到服务器端监听socket
  int listen_st = serverSt->getst();

  //epoll事件
  struct epoll_event ev;
  ev.data.fd = listen_st;

  //设定事件种类
  ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;

  //注册监听socket到epoll
  serverEpoll->addEpoll(listen_st, ev);

  int st = 0;
  while(1) {
    //获得有事件socket的个数
    int nfds = serverEpoll->waitEpoll(-1);
    cout<<"发生了 : "<<nfds<<"个事件"<<endl;
    if(nfds == -1) {
      cout<<"epoll wait failed"<<strerror(errno);
      breadk;
    }

    int i;
    int fd;
    for(i = 0; i<nfds; i++) {
      //从epoll中得到时间的文件描述符
      fd = serverEpoll->getfd(i);
      if(fd < 0) {
        continue;
      }

      struct sockaddr_in acceptSockAddr;
      //struct onlineArray insertArrayNode;
      //如果出发的事件是监听的socket，表示有新的客户端进行连接
      if(fd == listen_st) {
        //得到客户端socket
        st = serverSt->acceptSocket(listen_st, acceptSockAddr);

        //插入到在线列表中
        onlineDeviceTable->insertArray(st, acceptSockAddr);

        cout<<"recv st = "<<st<<"; and listen_st = "<<listen_st<<endl;
        cout<<"在线列表人数"<<onlineDeviceTable->getOnLineNum()<<endl;

        if(st > 0) {
          //设置为非阻塞
          setNoBlocking(st);
          ev.data.fd = st;
          ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
          //将客户端的socket加入epoll池
          serverEpoll->addEpoll(st, ev);
          continue;
        }
      }

      //不是得到新的socket
      //从epoll池中得到一个事件
      __uint32_t events = serverEpoll->getEvent(i);
      //得到该事件的socket
      st = serverEpoll->getfd(i);

      //是收到消息事件
      if(events & EPOLLIN) {
        cout<<"recv from : " <<st<<endl;
        char buffer[MAXSIZE];
        memset(&buffer, 0, sizeof(buffer));
        //从该socket接收消息
        serverSt->recvSocket(st, buffer);

        //如果接收buffer小于0
        if(strlen(buffer) <= 0) {
          serverSt->sendSocket(st);
          close(st);
        }
        //收到消息
        if(strlen(buffer) > 0) {
          cout<<"from "<<st<<" recv buffer : "<<buffer <<endl;
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
  onlineDevice *pOnlineDevice = new onlineDevice();
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
  recvOprate.onlineDeviceTable = pOnlineDevice;
  sendOprate.pLinkTable = pQueuePool->getSendTable();
  doubleOperate.pRecvTable = recvOprate.pLinkTable;
  doubleOperate.pSendTable = sendOprate.pLinkTable;
  doubleOperate.onlineDeviceTable = pOnlineDevice;
  pthread_t thrd1, thrd2, thrd3, thrd4;
  //启动接收线程
  pthread_create(&thrd1, NULL, epollRecv, &recvOprate);
  pthread_create(&thrd3, NULL, epollAnalyze, &doubleOperate);
  //pthread_create(&thrd2, NULL, epollSend, &sendOprate);

  //启动线程池
  //新建三个线程，传入发送，接收列表
  /*
  threadControl *pthreadControl = new threadControl(3,sendOprate.pLinkTable, recvOprate.pLinkTable, pOnlineDevice);
  classpoint *threadPool = (struct classpoint *)malloc(sizeof(classpoint))  ;
  threadPool->pThreadPool = pthreadControl->getThreadPool();
  pthread_t thrdHeart;
  pthread_create(&thrdHeart, NULL, threadControl::heartBreath, threadPool);
  */
  while(1) {}
  return 0;
}
