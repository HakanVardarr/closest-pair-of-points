CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude 

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objects

OBJS = $(OBJ_DIR)/cpp.o \
       $(OBJ_DIR)/cppAP.o \
       $(OBJ_DIR)/cppDC.o

TARGET = $(BUILD_DIR)/benchmark

all: directories $(OBJS) $(TARGET)

directories:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/cpp.o: $(SRC_DIR)/cpp.c $(INC_DIR)/cpp.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/cppAP.o: $(SRC_DIR)/cppAP.c $(INC_DIR)/cpp.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/cppDC.o: $(SRC_DIR)/cppDC.c $(INC_DIR)/cpp.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(SRC_DIR)/benchmark.c $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lm

clean:
	rm -rf $(BUILD_DIR)
