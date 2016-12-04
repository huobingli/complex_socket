
//********************************************************
//
//       FileName:      kuangjia.md
//
//       Author:  huobingli - huobingli@outlook.com
//       Description:    
//       Create: 2016-12-01  19:10:35
//       Last Modified: 2016-12-01 19:10:35
//********************************************************

#### 结构框架

.   
├── client   
│   ├── client.cpp   
│   └── clientSocket.cpp
├── common   
│   ├── cacheTable.cpp   
│   └── socket.cpp   
├── kuangjia.md   
├── QueueControl.h    
├── README.md   
└── server   
    ├── epoll.cpp   
    ├── messQueueControl.cpp   
    ├── server.cpp   
    ├── threadControl.cpp   
    └── threadPool.cpp   

#### client文件夹   
##### clientSocket.cpp   

clientSocket
```
class clientSocket {
private:
  bool m_Connected;
  struct sockaddr_in m_ClientAddr;
  int m_Socket;
  int m_Port;
  unsigned char m_IPAddress[16];

public:
  setIPPort();
  createSocket();
  connectServer();
  judgeFlag();
  getSt();
}
```


#### server文件夹
##### serverSocket.cpp
