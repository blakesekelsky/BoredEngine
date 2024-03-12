#include "Game.h"
#include "TextureManager.h"

SDL_Texture *keyTex;
int count;
bool countUp;
SDL_Rect srcR, destR;

Game::Game() {
  printf("Game constructor\n");
}

Game::~Game() {
  printf("Game destructor\n");
}

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
  countUp = true;
  keyTex = TextureManager::LoadTexture("assets/key.png", renderer);
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

void Game::render() {
  SDL_RenderClear(renderer);
  
  // render key image
  SDL_RenderCopy(renderer, keyTex, NULL, &destR);  

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  printf("Game cleaned\n");
}

void Game::update() {
  // bounce the key image back and forth horizontally
  if (count + destR.w > SDL_GetWindowSurface(window)->w) {
    countUp = false;
  } else if (count <= 0) {
    countUp = true;
  }

  if (countUp) {
    count++;
  } else {
    count--;
  }

  destR.x = count;
  destR.y = (SDL_GetWindowSurface(window)->h / 2) - 64;
  destR.h = 128;
  destR.w = 128;

  printf("Count: %d\n", count);
}