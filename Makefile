binary:
	g++ src/Game.h src/Game.cpp src/TextureManager.h src/TextureManager.cpp src/main.cpp -w -lSDL2 -lSDL2_image -o bin/main

build_run: binary
	./bin/main

run:
	./bin/main