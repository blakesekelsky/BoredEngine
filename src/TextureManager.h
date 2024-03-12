#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
  public:
    static SDL_Texture *LoadTexture(const char *fileName, SDL_Renderer *ren);
};

#endif