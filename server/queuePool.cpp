#include "cacheTable.cpp"
#ifndef _QUEUEPOOL_CPP
#define _QUEUEPOOL_CPP
class queuePool {
private:
	cacheTable *sendTable;
	cacheTable *recvTable;

public:
	queuePool() {
		sendTable = new cacheTable(20);
		recvTable = new cacheTable(20);
	}

	~queuePool() {}

	cacheTable *getSendTable() {
		return sendTable;
	}

	cacheTable *getRecvTable() {
		return recvTable;
	}
};
#endif
