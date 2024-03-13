#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {
  public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;
    bool centered = false;

    int speed = 5;

    TransformComponent() {
      position.Zero();
    }

    // background moving around player
    TransformComponent(int sc, bool forceC, SDL_Window *window) {
      scale = sc;
      centered = forceC;
      position.x = (SDL_GetWindowSurface(window)->w / 2) - ((width * scale) / 2);
      position.y = (SDL_GetWindowSurface(window)->h / 2) - ((height * scale) / 2);
    }
    
    TransformComponent(float x, float y){
      position.x = x;
      position.y = y;
    }

    TransformComponent(int sc) {
      position.Zero();
      scale = sc;
    }

    TransformComponent(float x, float y, int w, int h, int sc){
      position.x = x;
      position.y = y;
      width = w;
      height = h;
      scale = sc;
    }

    void init() override {
      velocity.Zero();
    }

    void update() override {
      if (!centered) {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
      }
    }
};


#endif