#include "cacheLinkTable.cpp"
#ifndef _QUEUEPOOL_CPP
#define _QUEUEPOOL_CPP
class queuePool {
private:
	cacheLinkTable *sendTable;
	cacheLinkTable *recvTable;

public:
	queuePool() {
		sendTable = new cacheLinkTable(20);
		recvTable = new cacheLinkTable(20);
	}

	~queuePool() {}

	cacheLinkTable *getSendTable() {
		return sendTable;
	}

	cacheLinkTable *getRecvTable() {
		return recvTable;
	}
};
#endif