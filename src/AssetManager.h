#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS/ECS.h"
#include "Vector2D.h"

class AssetManager {
  public:
    AssetManager(Manager *man);
    ~AssetManager();

    void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
    
    void AddTexture(std::string id, const char *path);
    SDL_Texture *GetTexture(std::string id);
  private:
    Manager *manager;
    std::map<std::string, SDL_Texture *> textures;
};

#endif