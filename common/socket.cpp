
//********************************************************
//
//       FileName:      socket.cpp
//
//       Author:  huobingli - huobingli@outlook.com
//       Description:
//       Create: 2016-12-01  17:19:00
//       Last Modified: 2016-12-01 17:19:00
//********************************************************
//
#include <iostream>

#ifndef _SOCKET_CPP
#define _SOCKET_CPP

class socket{
private:
	//communication socket
	int m_St;
	//communication port
	int m_Port;
	//socket param;
	struct sockaddr_in m_SocketAddr;

public:
  socket(int iPort) {
    m_St = 0;
    m_Port = iPort;
    memset(&m_SocketAddr, 0, sizeof(m_SocketAddr));
  }

  ~socket() {}

  //create socket
  virtual void createSocket(); 

  int getSt() { return m_St; }

  //client socket need achieve this function
  virtual void connectServer();

};

#endif
