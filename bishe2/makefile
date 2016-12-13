cc=g++

start: serverSocket.o epoll.o CacheTable.o threadPool.o threadControl.o Thread.o workQueue.o onlineDevice.o MessageParse.o DbControl.o threadFuntion.o structClass.h
	$(cc) -o main main.cpp epoll.o CacheTable.o serverSocket.o onlineDevice.o MessageParse.o DbControl.o -lpthread -lmysqlclient
#main.o:  
#	$(cc) -c -o main.o main.cpp -lpthread
epoll.o: epoll.h
	$(cc) -c -o epoll.o epoll.cpp
CacheTable.o: CacheTable.h
	$(cc) -c -o CacheTable.o CacheTable.cpp
serverSocket.o: serverSocket.h
	$(cc) -c -o serverSocket.o serverSocket.cpp
threadControl.o: threadControl.h
	$(cc) -c -o threadControl.o threadControl.cpp -lpthread
threadPool.o: threadPool.h
	$(cc) -c -o threadPool.o threadPool.cpp -lpthread
Thread.o: Thread.h
	$(cc) -c -o Thread.o Thread.cpp -lpthread
workQueue.o: workQueue.h
	$(cc) -c -o workQueue.o workQueue.cpp
onlineDeivce.o: onlineDevice.h
	$(cc) -c -o onlineDevice.o onlineDevice.cpp
DbControl.o: DbControl.h
	$(cc) -c -o DbControl.o DbControl.cpp -lmysqlclient
MessageParse.o: MessageParse.h
	$(cc) -c -o MessageParse.o MessageParse.cpp
threadFuntion.o: structClass.h 
	$(cc) -c -o threadFuntion.o threadFuntion.h
clean:
	rm -f *.o
