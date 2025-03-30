CC=gcc
CFLAGS=-std=c2x -Wall -Wextra -Werror -g -ftest-coverage -fprofile-arcs -coverage
LDFLAGS=-lraylib

build: satellite.c
	$(CC) satellite.c $(CFLAGS) $(LDFLAGS) -o satellite

build-strict:
	$(CC) satellite.c $(CFLAGS) -pedantic $(LDFLAGS) -o satellite

coverage:
	make clean
	make build
	gcovr .

run: 
	./satellite

clean: 
	rm -f ./satellite

all: clean build run
cover: clean build coverage
