#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject *key;
GameObject *key2;
GameObject *trick;

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
  key = new GameObject("assets/key.png", renderer, 0, 0, 128, 128);
  trick = new GameObject("assets/trick.png", renderer, (SDL_GetWindowSurface(window)->w-128)/2, (SDL_GetWindowSurface(window)->w-128)/2, 128, 128);
  key2 = new GameObject("assets/key.png", renderer, SDL_GetWindowSurface(window)->w-128, SDL_GetWindowSurface(window)->h-128, 128, 128);
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
  // update key game object, (pass window for collision)
  key->Update(window);
  trick->Update(window);
  key2->Update(window);
}

void Game::render() {
  SDL_RenderClear(renderer);
  
  // render key game object
  key->Render();
  trick->Render();
  key2->Render();

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  printf("Game cleaned\n");
}