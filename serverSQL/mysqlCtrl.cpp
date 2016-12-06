
//********************************************************
//
//       FileName:      mysqlCtrl.cpp
//
//       Author:         
//       Description:    
//       Create:        2016-12-06 19:25:28
//       Last Modified: 2016-12-06 19:25:28
//********************************************************


//#include "mysqlCtrl.h"
#include <mysql/mysql.h>
#include <iostream>
using namespace std;

#ifndef _MYSQLCTRL_CPP_
#define _MYSQLCTRL_CPP_
class mysqlCtrl {
private:
  MYSQL  m_mysql;
  int m_connection;
public:
  mysqlCtrl() {
    m_connection = 0;
  }

  ~mysqlCtrl() {}

  void initMysql() {
    mysql_init(&m_mysql);
  }

  bool connectMysql() {
    if(mysql_real_connect(&m_mysql, "localhost", "root", "123456", "ssm", 3306, NULL, 0)) {
      m_connection = 1;
      cout<<"connect MySQL successed!!!"<<endl;
      return true;
    } else {
      cout<<"connect MySQL failed..."<<endl;
      return false;
    }
  }   

  bool operateMysql(const char *pSql, int iLength) {
    if(m_connection == 0) {
      cout<<"MySQL is not connected!"<<endl;
      return false;
    }
    if(mysql_query(&m_mysql, pSql)) {
      cout<<"query successed!"<<mysql_affected_rows(&m_mysql)<<endl;
      return true;
    } else { 
      cout<<mysql_error(&m_mysql)<<endl;
      return false;
    } 
  }

  void disconnectMysql() {
    mysql_close(&m_mysql);
    m_connection = 0;
  }
};
#endif
