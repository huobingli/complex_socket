cc=g++
start:  mysqlCtrl.cpp 
	$(cc) -o test test.cpp -lmysqlclient
mysqlCtrl.o:
	$(cc) -c -o mysqlCtrl.o mysqlCtrl.cpp -lmysqlclient
clean:
	rm -f *.o
