CC=g++
CFLAGS=-std=c++23 -Wall -Wextra -Werror -Wno-missing-field-initializers -g
COVFLAGS=-ftest-coverage -fprofile-arcs -coverage
LDFLAGS=-lraylib -lm

build: satellite.cpp
	$(CC) satellite.cpp $(CFLAGS) $(LDFLAGS) -o satellite

build-strict:
	$(CC) satellite.cpp $(CFLAGS) -pedantic $(LDFLAGS) -o satellite

build-cover: 
	$(CC) satellite.cpp $(CFLAGS) $(COVFLAGS) $(LDFLAGS) -o satellite

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
