# Makefile for CS210 PA1
CC = g++
# Defines which version of c++ to use, the newest version on edoras is C++11
CFLAGS = -g -std=c++11

SortableArray: PA1TestDriver.o SortableArray.o
	$(CC) $(CFLAGS) -o SortableArray PA1TestDriver.o SortableArray.o

PA1TestDriver.o: PA1TestDriver.cpp SortableArray.h
	$(CC) $(CFLAGS) -c PA1TestDriver.cpp

SortableArray.o: SortableArray.cpp SortableArray.h
	$(CC) $(CFLAGS) -c SortableArray.cpp

clean:
	rm -f *.o SortableArray
