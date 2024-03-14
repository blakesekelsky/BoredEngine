#include "Game.h"
#include "Map.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

extern Manager manager;

Map::Map(std::string tId, int ms, int ts) : texId(tId), mapScale(ms), tileSize(ts) {
  scaledSize = ms * ts;
};

Map::~Map() {
}


void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
  auto &tile(manager.addEntity());
  tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texId);
  tile.addGroup(Game::groupMap);
}

void Map::LoadMapTiles(std::string path, int sizeX, int sizeY) {
  std::ifstream mapfile(path);
  std::string line;

  while (std::getline(mapfile, line)) {
      std::istringstream ss(line);
      std::vector<int> row;
      std::string value;

      while (std::getline(ss, value, ',')) {
          row.push_back(std::stoi(value));
      }

      mapTileData.push_back(row);
  }
  mapfile.close();

  // render the map tiles
  for (int y = 0; y < sizeY; ++y) {
    for (int x = 0; x < sizeX; ++x) {
        int tileCode = mapTileData[y][x];
        int srcX = tileCode % 10;
        int srcY = tileCode / 10;
        AddTile(srcX * tileSize, srcY * tileSize, x * scaledSize, y * scaledSize);
    }
  }
}

void Map::LoadMapCollisionTiles(std::string path, int sizeX, int sizeY) {
  std::ifstream mapfile(path);
  std::string line;

  while (std::getline(mapfile, line)) {
    std::istringstream ss(line);
    std::vector<int> row;
    std::string value;

    while (std::getline(ss, value, ',')) {
        row.push_back(std::stoi(value));
    }

    mapCollisionData.push_back(row);
  }
  mapfile.close();

  // render the map collision tiles
  for (int y = 0; y < sizeY; y++) {
    for (int x = 0; x < sizeX; x++) {
      int collisionCode = mapCollisionData[y][x];
      if (collisionCode == 1) {
        auto &tcol(manager.addEntity());
        tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
        tcol.addGroup(Game::groupColliders);
      }
    }
  } 
}
