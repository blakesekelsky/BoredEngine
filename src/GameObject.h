#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Game.h"

class GameObject {
  public:
    GameObject(const char *texturesheet, SDL_Renderer *ren, int x, int y, int w, int h);
    ~GameObject();

    void Update(SDL_Window *window);
    void Render();
  private:
    int xpos;
    int ypos;
    int width;
    int height;

    SDL_Texture *objTexture;
    // no srcRect because we're using the entire texture for now
    SDL_Rect destRect;
    SDL_Renderer *renderer;
};

#endif