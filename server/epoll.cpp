#include <iostream>
#include <stdint.h>
#include <sys/epoll.h>

using namespace std;

#ifndef _EPOLL_CPP
#define _EPOLL_CPP

class epoll {
private:
	int iMaxLink;// max link num
	int iEpfd; //
	struct epoll_event *pEvents;
	int iLinkNum;//linked num
public:
	epoll(int num) {
		iMaxLink = num;
		pEvents = NULL;
		iLinkNum = 0;
	}

	~epoll() {}

	// create Epoll
	int createEpoll() {
		if(iMaxLink < 0)
			cout<<"error, iMaxLink cannot xiaoyu 0";
		iEpfd = epoll_create(iMaxLink);

		pEvents = new epoll_event[iMaxLink + 1];
	}

	//epoll wait events triger
	int waitEpoll(int second) {
		return epoll_wait(iEpfd, pEvents, iMaxLink, second);
	}

	//zhuce event into epoll
	void addEpoll(int st, struct epoll_event ev) {
		epoll_ctl(iEpfd, EPOLL_CTL_ADD, st, &ev);
	}

	//delete event from epoll
	void deleteEpoll(int st, struct epoll_event ev) {
		epoll_ctl(iEpfd, EPOLL_CTL_DEL, st, &ev);
	}

	//get events fd
	__uint32_t getEvent(int i) {
		return pEvents[i].events;
	}

	int getfd(int i) {
		return pEvents[i].data.fd;
	}

	void get()
	{
		cout<<"iMaxLink" <<iMaxLink<<"iLinkNum"<<iLinkNum<<endl;
	}
};

#endif
