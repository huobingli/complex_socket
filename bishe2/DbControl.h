/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DbControl.h
 * Author: 炳雳
 *
 * Created on 2016年12月9日, 上午11:27
 */
#include <mysql/mysql.h>

#include <iostream>
using namespace std;

#ifndef DBCONTROL_H
#define DBCONTROL_H

class DbControl{
private:
  MYSQL m_Mysql;
  int m_Connection; 

public:
  DbControl();
  ~DbControl();

  void initMysql();
  bool connectMysql();
  bool operateMysql(const char *pSql, int i);
  void disconnectMysql(); 
};

#endif /* DBCONTROL_H */

