CFLAGS = -Wall


all: lightxml.o runtest.exe

lightxml.o: lightxml.cpp lightxml.h
	g++ -c $(CFLAGS) -o lightxml.o lightxml.cpp

runtest.exe: test.cpp lightxml.o lightxml.h
	g++ $(CFLAGS) -o runtest.exe test.cpp lightxml.o

test: all
	./runtest
