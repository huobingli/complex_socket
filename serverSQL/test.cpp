
//********************************************************
//
//       FileName:      test.cpp
//
//       Author:         
//       Description:    
//       Create:        2016-12-06 19:50:26
//       Last Modified: 2016-12-06 19:50:26
//********************************************************


#include "mysqlCtrl.cpp" 
#include <iostream> 
using namespace std;

int main() {
  cout<<11<<endl;
  mysqlCtrl *m = new mysqlCtrl();

  m->initMysql();
  m->connectMysql();
  char *sql = "insert into administrator(id, name, password) values(2, 'balabala', '321654')";
  m->operateMysql(sql, 0);
  m->disconnectMysql();
  return 0;
}
