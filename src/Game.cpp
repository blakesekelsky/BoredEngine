#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

Manager manager;
Map *map;

SDL_Renderer *Game::renderer = nullptr;
auto &key(manager.addEntity());

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

  // ecs implimentation
  key.addComponent<TransformComponent>(500, 500);
  key.addComponent<SpriteComponent>("assets/key.png");
}

void Game::handleEvents() {
  SDL_Event event;
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

  key.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
  if (key.getComponent<TransformComponent>().position.x > 800) {
    key.getComponent<TransformComponent>().position.Subtract(Vector2D(864, 0));
  }
}

void Game::render() {
  SDL_RenderClear(renderer);
  
  map->DrawMap();
  manager.draw();

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  printf("Game cleaned\n");
}