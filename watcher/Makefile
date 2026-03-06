CC=gcc
CFLAGS=-std=c2x -Wall -Wextra -Werror
LDFLAGS=-lraylib -lm

build: watcher.c
	$(CC) watcher.c $(CFLAGS) $(LDFLAGS) -o watcher

build-strict:
	$(CC) watcher.c $(CFLAGS) -pedantic $(LDFLAGS) -o watcher

coverage:
	make clean
	make build
	gcovr .

run: 
	./watcher

clean: 
	rm -f ./watcher

all: clean build run
cover: clean build coverage
