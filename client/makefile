CC = g++
XX = g++
CFLAGS = -Wall -D_REENTRANT -g -std=c++11
INCLUDE = 

LIBS = -lpthread
OBJS = client.cpp
TEST = client

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
%.o: %.cpp
	$(cc) $(CFLAGS) $(INCLUDE) -c %< -o $@
all: $(TEST)

$(TEST): $(OBJS)
	$(XX) -o $(TEST) $(OBJS) $(LIBS)

clean:
	rm -f *.o
