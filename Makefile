CC=g++
CFLAGS=-std=c++23 -Wall -Wextra -Werror -Wno-missing-field-initializers -Wno-misleading-indentation -Wno-unused-variable -g
COVFLAGS=-ftest-coverage -fprofile-arcs -coverage
LDFLAGS=-lraylib 
INFILES=satellite.cpp player.cpp rlimgui/rlImGui.cpp imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp

build: $(INFILES)
	$(CC) $(INFILES) $(CFLAGS) $(LDFLAGS) -o satellite

build-strict:
	$(CC) $(INFILES) $(CFLAGS) -pedantic $(LDFLAGS) -o satellite

build-cover: 
	$(CC) $(INFILES) $(CFLAGS) $(COVFLAGS) $(LDFLAGS) -o satellite

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
