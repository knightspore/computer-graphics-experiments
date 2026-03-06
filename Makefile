CC=gcc
CFLAGS=-std=c2x -Wall -Wextra -Werror
LDFLAGS=-lraylib -lm

build: jet-hud.c
	$(CC) jet-hud.c $(CFLAGS) $(LDFLAGS) -o jet-hud

build-strict:
	$(CC) jet-hud.c $(CFLAGS) -pedantic $(LDFLAGS) -o jet-hud

coverage:
	make clean
	make build
	gcovr .

run: 
	./jet-hud

clean: 
	rm -f ./jet-hud

all: clean build run
cover: clean build coverage
