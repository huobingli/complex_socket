
//*****************************************************
//
//    FileName:      client.cpp
//
//    Author:         huobingli - huobingli@outlook.com
//    Description:    
//    Create:        2016-12-03 21:06:43
//    Last Modified: 2016-12-03 21:06:43
//****************************************************
//
#include <iostream>
#include "clientSocket.cpp"

int main(int arg, char *argv[]) {
     if(arg < 2) return 0;
     std::cout<<atoi(argv[1])<<std::endl;
     std::cout<<argv[2]<<std::endl;
//   clientSocket *client = new client
     return 0;
}
