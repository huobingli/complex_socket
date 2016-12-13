<<<<<<< HEAD
#include "cacheLinkTable.cpp"
=======
#include "cacheTable.cpp"
>>>>>>> 5ef238650f41a5baca738e1df2f7ed65ee074aac
#ifndef _QUEUEPOOL_CPP
#define _QUEUEPOOL_CPP
class queuePool {
private:
<<<<<<< HEAD
	cacheLinkTable *sendTable;
	cacheLinkTable *recvTable;

public:
	queuePool() {
		sendTable = new cacheLinkTable(20);
		recvTable = new cacheLinkTable(20);
=======
	cacheTable *sendTable;
	cacheTable *recvTable;

public:
	queuePool() {
		sendTable = new cacheTable(20);
		recvTable = new cacheTable(20);
>>>>>>> 5ef238650f41a5baca738e1df2f7ed65ee074aac
	}

	~queuePool() {}

<<<<<<< HEAD
	cacheLinkTable *getSendTable() {
		return sendTable;
	}

	cacheLinkTable *getRecvTable() {
		return recvTable;
	}
};
#endif
=======
	cacheTable *getSendTable() {
		return sendTable;
	}

	cacheTable *getRecvTable() {
		return recvTable;
	}
};
#endif
>>>>>>> 5ef238650f41a5baca738e1df2f7ed65ee074aac
