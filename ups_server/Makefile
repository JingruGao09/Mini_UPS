CC=g++
CFLAGS=-std=gnu++11 -pedantic -Wall -Werror -ggdb3 -pthread 
EXTRAFLAGS=-lpqxx -lpq
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o,$(SRCS))
SRCS2=$(wildcard *.cc)
OBJS2=$(patsubst %.cc, %.o,$(SRCS2))
Mini_ups:$(OBJS) $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(OBJS2) $(EXTRAFLAGS) `pkg-config --cflags --libs protobuf`
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<
%.o:%.cc
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f Mini_ups *.o *~ test testab UPS.log a.out

test:
	g++ -ggdb3 test.cpp helper.cpp webridge.cpp server.cpp web_ups.pb.cc -o test `pkg-config --cflags --libs protobuf` $(EXTRAFLAGS)

testab:
	g++ -ggdb3 helper.cpp log.cpp dbinterface.cpp client.cpp world_ups.pb.cc worldbridge.cpp ups_amazon.pb.cc amazonbridge.cpp -o testab `pkg-config --cflags --libs protobuf` $(EXTRAFLAGS)
