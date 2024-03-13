#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"

Manager manager;
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;

SDL_Rect Game::camera = {0, 0, 800, 640};

auto& player(manager.addEntity());

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
  map = new Map("assets/terrain_ss.png", 2, 32);
  map->LoadMapTiles("assets/tiles.map", 25, 20);
  map->LoadMapCollisionTiles("assets/collision.map", 25, 20);

  // player components
  player.addComponent<TransformComponent>(2, false, Game::window);
  player.addComponent<SpriteComponent>("assets/player_anim.png", true);
  player.addComponent<KeyboardController>();
  player.addComponent<ColliderComponent>("player");
  player.addGroup(groupPlayers);
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

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));

void Game::update() {
  SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
  Vector2D playerPos = player.getComponent<TransformComponent>().position;

  manager.refresh();
  manager.update();

  for (auto &c : colliders) {
    SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
    if (Collision::AABB(playerCol, cCol)) {
      player.getComponent<TransformComponent>().position = playerPos;
    }
  }

  camera.x = player.getComponent<TransformComponent>().position.x - 400;
  camera.y = player.getComponent<TransformComponent>().position.y - 320;

  if (camera.x < 0) {
    camera.x = 0;
  }
  if (camera.x > camera.w) {
    camera.x = camera.w;
  } 
  if (camera.y < 0) {
    camera.y = 0;
  }
  if (camera.y > camera.h) {
    camera.y = camera.h;
  }

}

void Game::render() {
  SDL_RenderClear(renderer);
  
  for (auto &t : tiles) {
    t->Draw();
  }

  for (auto &c : colliders) {
    c->Draw();
  }

  for (auto &p : players) {
    p->Draw();
  }

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  printf("Game cleaned\n");
}