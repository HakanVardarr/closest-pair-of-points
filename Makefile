CC = gcc
CFLAGS = -Wall -Wextra -O2

all: cppAP cppDC

cpp.o: cpp.c cpp.h
	$(CC) $(CFLAGS) -c cpp.c -o cpp.o

cppAP: cppAP.c cpp.o
	$(CC) $(CFLAGS) cppAP.c cpp.o -o cppAP -lm

cppDC: cppDC.c cpp.o
	$(CC) $(CFLAGS) cppDC.c cpp.o -o cppDC -lm

clean:
	rm -f cpp.o cppAP cppDC
