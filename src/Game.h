#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <vector>
#include "AssetManager.h"

class ColliderComponent;
class AssetManager;

class Game {
  public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
    static AssetManager *assets;

    bool running() { return isRunning; }

    enum groupLabels : std::size_t{
      groupMap,
      groupPlayers,
      groupColliders
    };
  private:
    SDL_Window *window;
};

#endif