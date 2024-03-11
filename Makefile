build:
	g++ Game.h Game.cpp main.cpp -w -lSDL2 -lSDL2_image -o bin/main

run:
	./bin/main

test: build run