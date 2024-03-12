binary:
	g++ src/Game.h src/Game.cpp src/TextureManager.h src/TextureManager.cpp src/Map.h src/Map.cpp src/Vector2D.h src/Vector2D.cpp src/Collision.h src/Collision.cpp src/main.cpp -w -lSDL2 -lSDL2_image -o bin/main

build_run: binary
	./bin/main

run:
	./bin/main