# Makefile for CS210 PA2
CC = g++
CFLAGS = -g -std=c++11
EXECUTABLES = PQOrdered PQLinkedList PQHeap
HEADERS = PriorityQueue.h TestDriver.h

all: $(EXECUTABLES)


PQOrdered: PQOrdered.o TestDriver.o
	$(CC) $(CFLAGS) -o PQOrdered PQOrdered.o TestDriver.o


PQOrdered.o: PQOrdered.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c PQOrdered.cpp


PQLinkedList: PQLinkedList.o TestDriver.o
	$(CC) $(CFLAGS) -o PQLinkedList PQLinkedList.o TestDriver.o

PQLinkedList.o: PQLinkedList.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c PQLinkedList.cpp


PQHeap: PQHeap.o TestDriver.o
	$(CC) $(CFLAGS) -o PQHeap PQHeap.o TestDriver.o

PQHeap.o: PQHeap.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c PQHeap.cpp


TestDriver.o: TestDriver.cpp TestDriver.h
	$(CC) $(CFLAGS) -c TestDriver.cpp


clean:
	rm -f *.o $(EXECUTABLES)
