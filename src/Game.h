#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <vector>

class ColliderComponent;

class Game {
  public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    static void AddTile(int srcX, int srcY, int x, int y);
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent *> colliders;

    bool running() { return isRunning; }
  private:
    bool isRunning;
    SDL_Window *window;
};

#endif