#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Components.h"
#include <SDL2/SDL.h>
#include "../TextureManager.h"

class SpriteComponent : public Component {
  private:
    TransformComponent *transform;
    SDL_Texture *texture;
    // SDL_Rect srcRect; --- uncomment when all sprites are uniform in size
    SDL_Rect destRect;
  
  public:
    SpriteComponent() = default;

    ~SpriteComponent() {
      SDL_DestroyTexture(texture);
    }

    SpriteComponent(const char *path) {
      setTex(path);
    }

    void setTex(const char *path) {
      texture = TextureManager::LoadTexture(path);
    }

    void init() override {
      transform = &entity->getComponent<TransformComponent>();

      // uncomment when all sprites are uniform in size
      // srcRect.x = srcRect.y = 0;
      // srcRect.w = srcRect.h = 32;
    }

    void update() override {
      destRect.w = transform->width * transform->scale;
      destRect.h = transform->height * transform->scale;
      destRect.x = (int)transform->position.x;
      destRect.y = (int)transform->position.y;
    }

    void draw() override {
      TextureManager::Draw(texture, destRect);
    }
};

#endif