cc=g++
start: server.o serverSocket.o epoll.o cacheTable.o threadPool.o threadControl.o serverAnalyze.o
	$(cc) -o server server.o  -lpthread
server.o: 
	$(cc) -c -o server.o server.cpp -lpthread
epoll.o: 
	$(cc) -c -o epoll.o epoll.cpp
cacheTable.o: 
	$(cc) -c -o cacheTable.o cacheTable.cpp
serverSocket.o: 
	$(cc) -c -o serverSocket.o serverSocket.cpp
serverAnalyze.o:
	$(cc) -c -o serverAnalyze.o serverAnalyze.cpp
threadControl.o:
	$(cc) -c -o threadControl.o threadControl.cpp -lpthread
threadPool.o:
	$(cc) -c -o threadPool.o threadPool.cpp -lpthread
clean:
	rm -f *.o

