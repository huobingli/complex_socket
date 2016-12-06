
//********************************************************
//
//       FileName:      serverSQL.cpp
//
//       Author:  huobingli - huobingli@outlook.com
//       Description:    
//       Create: 2016-12-05  13:59:04
//       Last Modified: 2016-12-05 13:59:04
//********************************************************
// 
#include <iostream>

using namespace std;

#ifndef _SERVERSQL_CPP
#define _SERVERSQL_CPP

#include "message.cpp"

class serverSQL {
private:
  MYSQL conn;

public:
  serverSQL() {
    mysql_init(&conn);
  }
  ~serverSQL() {}
  
  bool connectSQL() {
    return mysql_real_connect(&conn, "localhost", "root", "", "", 0,NULL,CLINET_FOUND_ROWS);
  }

  bool insertSQL(char *pBuffer, int iLength) {
    char buffer[100];
    bzero(&buffer, sizeof(buffer));
    memcpy(buffer, pBuffer, iLength);
    return mysql_query(&conn, buffer);
  }

  int searchSQL(char *pBuffer) {
  
  }

  bool updateSQL(char *pBuffer, int iLength) {
    return mysql_real_query() 
  }

  void closeSQL() {
    mysql_close(&conn);
  }
};

#endif
