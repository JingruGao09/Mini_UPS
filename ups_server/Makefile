CC=g++
CFLAGS=-std=gnu++11 -pedantic -Wall -Werror -ggdb3 -pthread 
EXTRAFLAGS=-lpqxx -lpq
SRCS=$(wildcard *.cpp,*.cc)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
Mini_ups:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(EXTRAFLAGS)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<
.PHONY: clean
clean:
	rm -f Mini_ups *.o *~ test

test:
	g++ -ggdb3 dbinterface.cpp client.cpp world_ups.pb.cc worldbridge.cpp -o test `pkg-config --cflags --libs protobuf` $(EXTRAFLAGS)
