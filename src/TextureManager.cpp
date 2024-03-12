#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
  SDL_Surface *tmpSurface = IMG_Load(fileName);
  SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
  SDL_FreeSurface(tmpSurface);
  
  return tex;
}

// uncomment when all sprites are uniform in size
// void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
//   SDL_RenderCopy(Game::renderer, tex, &src, &dest);
// }

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect dest) {
  SDL_RenderCopy(Game::renderer, tex, NULL, &dest);
}