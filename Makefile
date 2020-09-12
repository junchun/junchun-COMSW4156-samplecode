CC = g++
CFLAGS = -pg -Wall -std=c++11
#SRCS = main.cpp
SRCS = ${wildcard *.cpp}
OBJS = ${SRCS:.cpp=.o}
INCLS = ${SRCS:.cpp=.h} main.h chainingHash.h probingHash.h

p1: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o p3

$(OBJS):
	$(CC) $(CFLAGS) -c $*.cpp

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip $(SRCS) $(INCLS) Makefile

clean:
	rm -f *.o p3 core


