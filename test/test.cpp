
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
#include  <string.h>
#include <time.h>
using namespace std;
int main() {
	time_t timep;
	time(&timep);
	cout<<ctime(&timep)<<endl;
	unsigned char strTime[20] = {0};
		time_t time_UTC;
  		time(&time_UTC);
		
  		strftime((char *)strTime,100,"%Y/%m/%d/%T",localtime(&time_UTC));
	int l = strlen((char *)strTime);
	for(int i = 0; i < l; i++) 
  		cout<<strTime[i];
	cout<<endl;
	/*	pTime=localtime(&time_UTC);
        strTime[0]=(unsigned char)pTime->tm_sec; cout<<strTime[0]<<endl;
        strTime[1]=(unsigned char)pTime->tm_min; cout<<strTime[1]<<endl;
        strTime[2]=(unsigned char)pTime->tm_hour; cout<<strTime[2]<<endl;
        strTime[3]=(unsigned char)pTime->tm_mday; cout<<strTime[3]<<endl;
        strTime[4]=(unsigned char)pTime->tm_mon; cout<<strTime[4]<<endl;
        strTime[5]=(unsigned char)(pTime->tm_year-100); cout<<strTime[5]<<endl;
	*/
	return 0;
}
