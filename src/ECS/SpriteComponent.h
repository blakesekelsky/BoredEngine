#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Components.h"
#include <SDL2/SDL.h>
#include "../TextureManager.h"

class SpriteComponent : public Component {
  private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100; // milliseconds
  
  public:
    SpriteComponent() = default;

    ~SpriteComponent() {
      SDL_DestroyTexture(texture);
    }

    SpriteComponent(const char *path) {
      setTex(path);
    }

    SpriteComponent(const char *path, int nFrames, int mSpeed) {
        animated = true;
        frames = nFrames;
        speed = mSpeed;
        setTex(path);
    }

    void setTex(const char *path) {
      texture = TextureManager::LoadTexture(path);
    }

    void init() override {
      transform = &entity->getComponent<TransformComponent>();

      srcRect.x = srcRect.y = 0;
      srcRect.w = transform->width;
      srcRect.h = transform->height;
    }

    void update() override {
      if (animated) {
        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
      }

      destRect.w = transform->width * transform->scale;
      destRect.h = transform->height * transform->scale;
      destRect.x = (int)transform->position.x;
      destRect.y = (int)transform->position.y;
    }

    void draw() override {
      TextureManager::Draw(texture, srcRect, destRect);
    }
};

#endif