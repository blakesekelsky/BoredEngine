#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
  public:
    static SDL_Texture *LoadTexture(const char *fileName);
    // static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest); --- uncomment when all sprites are uniform in size
    static void Draw(SDL_Texture *tex, SDL_Rect dest);
};

#endif