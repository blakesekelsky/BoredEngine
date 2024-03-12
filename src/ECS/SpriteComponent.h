#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Components.h"
#include <SDL2/SDL.h>
#include "../TextureManager.h"

class SpriteComponent : public Component {
  private:
    PositionComponent *position;
    SDL_Texture *texture;
    // SDL_Rect srcRect; --- uncomment when all sprites are uniform in size
    SDL_Rect destRect;
  
  public:
    SpriteComponent() = default;
    SpriteComponent(const char *path) {
      setTex(path);
    }

    void setTex(const char *path) {
      texture = TextureManager::LoadTexture(path);
    }

    void init() override {
      position = &entity->getComponent<PositionComponent>();

      // uncomment when all sprites are uniform in size
      // srcRect.x = srcRect.y = 0;
      // srcRect.w = srcRect.h = 32;
      destRect.w = destRect.h = 64;
    }

    void update() override {
      destRect.x = position->x();
      destRect.y = position->y();
    }

    void draw() override {
      TextureManager::Draw(texture, destRect);
    }
};

#endif