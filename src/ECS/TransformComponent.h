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

    int speed = 5;

    TransformComponent() {
      position.x = 0.0f;
      position.y = 0.0f;
    }
    
    TransformComponent(float x, float y){
      position.x = x;
      position.y = y;
    }

    TransformComponent(int sc) {
      position.x = 0.0f;
      position.y = 0.0f;
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
      velocity.x = 0.0f;
      velocity.y = 0.0f;
    }

    void update() override {
      position.x += velocity.x * speed;
      position.y += velocity.y * speed;
    }
};


#endif