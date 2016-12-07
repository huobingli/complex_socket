#include <iostream>
#include <stdlib.h>

#include "package.cpp"

class serverAnalyze{
private:
	messagePackage *pMessagePackage;
public:
	serverAnalyze(){
		pMessagePackage = new messagePackage();
	}
	~serverAnalyze(){}

	void setBuffer(char *buffer) {
		//set buffer 
		pMessagePackage->setPackage(buffer);
		//divide buffer
		pMessagePackage->divideString();
	}

	void judgeBuffer() {
		if(pMessagePackage->getOperateLength() == 0) {
			cout<<"error package"<<endl;
			return ;
		} else {
			char pOperateType[5];
			memset(pOperateType, 0, sizeof(pOperateType));
			cout<<pOperateType<<endl;
			pMessagePackage->getOperateType(pOperateType);
			int iOperateType = bCharToInt(pOperateType);
			switch (iOperateType) {
				//
				case 1:
					cout<<"LOGINing"<<endl;
					handleLogin();
					break;
				//
				case 2:
					cout<<"CHECKing"<<endl;
					handleCheck();
					break;
				//
				case 3:
					cout<<"RESIGing"<<endl;
					handleResig();
					break;
				//
				case 4:
					cout<<"EXITSing"<<endl;
					handleExits();
					break;
				default:
					cout<<"no pipei de oeprate symbol"<<endl;
			}
		}
	}

	void handleLogin() {

	}

	void handleCheck() {
		cout<<"handleMessage"<<endl;
	}

	void handleResig() {

	}

	void handleExits() {

	}
};
