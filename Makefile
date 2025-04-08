OUT = main.exe
SRC = src/main.c

CC = gcc
CFLAGS = -g -Wall        
CFLAGS += -Iinclude      
LDFLAGS = -Llib -lSDL2main -lSDL2  

all: build run

build:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

debug:
	gdb -ex run ./$(OUT)

run:
	./$(OUT)
