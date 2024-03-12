#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *texturesheet, int x, int y, int w, int h) {
  xpos = x;
  ypos = y;
  width = w;
  height = h;

  objTexture = TextureManager::LoadTexture(texturesheet);
}

GameObject::~GameObject() {
  SDL_DestroyTexture(objTexture);
}

void GameObject::Update(SDL_Window *window) {
  // window border collision
  if (xpos + destRect.w >= SDL_GetWindowSurface(window)->w) {
    countUp = false;
  } else if (xpos <= 0) {
    countUp = true;
  }

  // horizontal movements
  if (countUp) {
    xpos++;
  } else {
    xpos--;
  }

  destRect.x = xpos;
  destRect.y = ypos;
  destRect.w = width;
  destRect.h = height;
}

void GameObject::Render() {
  SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}