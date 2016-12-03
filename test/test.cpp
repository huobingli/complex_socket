
//*****************************************************
//
//    FileName:      test.cpp
//
//    Author:         huobingli - huobingli@outlook.com
//    Description:    
//    Create:        2016-12-03 21:04:18
//    Last Modified: 2016-12-03 21:04:18
//****************************************************
//
#include <iostream>

#include <time.h>

int main() {
	time_t timep;
	time(&timep);
	std::cout<<ctime(&timep)<<std::endl;
	return 0;
}
