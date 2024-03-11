binary:
	g++ Game.h Game.cpp main.cpp -w -lSDL2 -lSDL2_image -o bin/main

build_run: binary
	./bin/main

run:
	./bin/main