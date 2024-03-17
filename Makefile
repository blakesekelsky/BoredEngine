binary:
	clang++ -stdlib=libc++ src/ECS/ECS.cpp src/Vector2D.cpp src/Collision.cpp src/Map.cpp src/Game.cpp src/AssetManager.cpp src/TextureManager.cpp src/main.cpp -w -lSDL2 -lSDL2_image -o bin/main

run: binary
	./bin/main