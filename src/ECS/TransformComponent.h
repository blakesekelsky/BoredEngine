#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Components.h"

class TransformComponent : public Component {
  public:
    TransformComponent() {
      xpos = ypos = 0;
    }
    
    TransformComponent(int x, int y){
      xpos = x;
      ypos = y;
    };

    int x() {return xpos;}
    int y() {return ypos;}

    void setPos(int x, int y) {
      xpos = x;
      ypos = y;
    }

    void init() override {}

    void update() override {
      xpos++;
      ypos++;
    }

  private:
    int xpos; 
    int ypos;
};


#endif