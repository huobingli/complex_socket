/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: 炳雳
 *
 * Created on 2016年12月8日, 下午7:52
 */

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
using namespace std;

#include "epoll.h"
#include "cacheTable.h"
#include "onlineDevice.h"
#include "serverSocket.h"
#include "threadControl.h"

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

/*
 * 
 */
int main(int argc, char** argv) {

    return 0;
}

