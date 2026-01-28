CC = gcc
CFLAGS = -Wall -Wextra -O2

# Default target
all: cpp.o cppAP.o cppDC.o benchmark

# Common shared functions
cpp.o: cpp.c cpp.h
	$(CC) $(CFLAGS) -c cpp.c -o cpp.o

# Brute-force algorithm object
cppAP.o: cppAP.c cpp.h
	$(CC) $(CFLAGS) -c cppAP.c -o cppAP.o

# Divide & Conquer algorithm object
cppDC.o: cppDC.c cpp.h
	$(CC) $(CFLAGS) -c cppDC.c -o cppDC.o

# Benchmark executable (when you need it)
benchmark: benchmark.c cpp.o cppAP.o cppDC.o
	$(CC) $(CFLAGS) benchmark.c cpp.o cppAP.o cppDC.o -o benchmark -lm

clean:
	rm -f *.o benchmark
