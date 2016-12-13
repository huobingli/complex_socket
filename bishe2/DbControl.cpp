/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DbControl.cpp
 * Author: 炳雳
 * 
 * Created on 2016年12月9日, 上午11:27
 */

#include "DbControl.h"

DbControl::DbControl() {
    m_Connection = 0;
}

DbControl::~DbControl() {
}

void DbControl::initMysql() {
    mysql_init(&m_Mysql);
}

bool DbControl::connectMysql() {
    if (mysql_real_connect(&m_Mysql, "localhost", "root", "123456", "ssm", 3306, NULL, 0)) {
        m_Connection = 1;
        cout << "connect MySQL successed!!!" << endl;
        return true;
    } else {
        cout << "connect MySQL failed..." << endl;
        return false;
    }
}

bool DbControl::operateMysql(const char *pSql, int iLength) {
    if (m_Connection == 0) {
        cout << "MySQL is not connected!" << endl;
        return false;
    }
    if (mysql_query(&m_Mysql, pSql)) {
        cout << "query successed!" << mysql_affected_rows(&m_Mysql) << endl;
        return true;
    } else {
        cout << mysql_error(&m_Mysql) << endl;
        return false;
    }
}

void DbControl::disconnectMysql() {
    mysql_close(&m_Mysql);
    m_Connection = 0;
}
