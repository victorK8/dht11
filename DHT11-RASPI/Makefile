# Compiler
CC = g++

# Includes
INCLUDE_DIR = include

# Source Code Path
SRC_DIR = src

# Flags to compiler
CFLAGS = -I$(INCLUDE_DIR) -lwiringPi

# Files to compile
SRCS = $(SRC_DIR)/dht11.c $(SRC_DIR)/test.c

# EXE NAME
EXE = test

all: $(EXE) 

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) -o bin/$(EXE) $(SRCS)

clean:
	rm bin/$(EXE)
