
//********************************************************
//
//       FileName:      mysqlCtrl.h
//
//       Author:         
//       Description:    
//       Create:        2016-12-06 19:09:38
//       Last Modified: 2016-12-06 19:09:38
//********************************************************

#include <mysql/mysql.h>

#ifndef _MYSQLCTRL_H_
#define _MYSQLCTRL_H_

class mysqlCtrl{
private:
  MYSQL *m_mysql;
  int m_connection; 

public:
  mysqlCtrl();
  ~mysqlCtrl();

  void initMysql();
  bool connectMysql();
  bool operateMysql(const char *pSql, int i);
  void disconnectMysql(); 
};

#endif
