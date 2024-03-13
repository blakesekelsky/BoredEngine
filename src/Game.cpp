#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"

Map* map;
const char* mapfile = "assets/terrain_ss.png";

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupColliders
};

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
  Map::LoadMap("assets/map.map", 25, 20);

  // player components
  player.addComponent<TransformComponent>(2, true, Game::window);
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

auto &tiles(manager.getGroup(groupMap));
auto &players(manager.getGroup(groupPlayers));

void Game::update() {
  manager.refresh();
  manager.update();

  Vector2D pVel = player.getComponent<TransformComponent>().velocity;
  int pSpeed = player.getComponent<TransformComponent>().speed;

  for (auto t : tiles) {
    t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
    t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
  }

  for (auto cc : colliders) {
    Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
  }
}

void Game::render() {
  SDL_RenderClear(renderer);
  
  // render each groupTile layer
  for (auto &t : tiles) {
    t->Draw();
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

void Game::AddTile(int srcX, int srcY, int xpos, int ypos) {
  auto &tile(manager.addEntity());
  tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
  tile.addGroup(groupMap);
}