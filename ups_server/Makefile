CC=g++
CFLAGS=-std=gnu++11 -pedantic -Wall -Werror -ggdb3 -pthread
EXTRAFLAGS=-lpqxx -lpq
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
Mini_ups:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(EXTRAFLAGS)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<
.PHONY: clean
clean:
	rm -f EXCHMatchServer *.o *~ a.out
