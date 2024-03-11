#include "Game.h"

SDL_Texture *keyTex;
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
  SDL_Surface *tmpSurface = IMG_Load("assets/key.png");
  keyTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
  SDL_FreeSurface(tmpSurface);
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
  // set key image on screen
  destR.x = (SDL_GetWindowSurface(window)->w / 2) - 64;
  destR.y = (SDL_GetWindowSurface(window)->h / 2) - 64;
  destR.h = 128;
  destR.w = 128;

}