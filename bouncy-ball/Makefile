CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c2x -pedantic -O2
LDFLAGS = -lm -lraylib

build: main.c
	$(CC) main.c $(CFLAGS) $(LDFLAGS) -o main

clean: main
	rm main

run: main
	./main

all: clean build run

