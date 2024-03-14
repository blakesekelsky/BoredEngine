#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <string>
#include <SDL2/SDL.h>
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
  public:
    SDL_Rect collider;
    std::string tag;

    SDL_Texture *tex;
    SDL_Rect srcR, destR;

    TransformComponent *transform;

    ColliderComponent(std::string t, int xpos, int ypos, int size) {
      tag = t;
      collider.x = xpos;
      collider.y = ypos;
      collider.w = collider.h = size;
    }

    void init() override {
      if (!entity->hasComponent<TransformComponent>()) {
        entity->addComponent<TransformComponent>();
      }
      transform = &entity->getComponent<TransformComponent>();

      tex = Game::assets->GetTexture("collision");

      srcR = {0, 0, 32, 32};
      destR = {collider.x, collider.y, collider.w, collider.h};
    }

    void update() override {
      if (tag != "terrain") {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
      }

      // to follow camera
      destR.x = collider.x - Game::camera.x;
      destR.y = collider.y - Game::camera.y;
    }

    void draw() override {
      TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};

#endif