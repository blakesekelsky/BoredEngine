#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"

Manager manager;
Map *map;

// key entity
auto &key(manager.addEntity());

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent *> Game::colliders;

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
  int flags = 0;

  // Set the window to fullscreen if the fullscreen flag is true
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    printf("Subsystems initialized\n");
    
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) {
      printf("Window created\n");
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      printf("Renderer created\n");
      isRunning = true;
    } else {
      isRunning = false;
    }
  } else {
    printf("SDL init failed\n");
  }

  // set key texture on surface
  map = new Map();
  map->LoadMap("assets/16x16.map", 16, 16);

  // key components
  key.addComponent<TransformComponent>(2);
  key.addComponent<SpriteComponent>("assets/key.png");
  key.addComponent<KeyboardController>();
  key.addComponent<ColliderComponent>("key");
}

void Game::handleEvents() {
  
  SDL_PollEvent(&event);

  switch(event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    default:
      break;
  }
}

void Game::update() {
  manager.refresh();
  manager.update();

  for (auto cc : colliders) {
    Collision::AABB(key.getComponent<ColliderComponent>(), *cc);
  }
}

void Game::render() {
  SDL_RenderClear(renderer);
  
  // map->DrawMap();
  manager.draw();

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  printf("Game cleaned\n");
}

void Game::AddTile(int id, int x, int y) {
  auto &tile(manager.addEntity());
  tile.addComponent<TileComponent>(x, y, 32, 32, id);
  tile.addComponent<ColliderComponent>("terrain");
}