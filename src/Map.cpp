#include "Game.h"
#include "Map.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

Map::Map() {
}

Map::~Map() {
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
  std::ifstream mapfile(path);
  std::string line;
  std::vector<std::vector<int>> mapdata;

  while (std::getline(mapfile, line)) {
      std::istringstream ss(line);
      std::vector<int> row;
      std::string value;

      while (std::getline(ss, value, ',')) {
          row.push_back(std::stoi(value));
      }

      mapdata.push_back(row);
  }

  for (int y = 0; y < sizeY; ++y) {
      for (int x = 0; x < sizeX; ++x) {
          int tileCode = mapdata[y][x];
          int srcX = tileCode % 10;
          int srcY = tileCode / 10;
          Game::AddTile(srcX * 32, srcY * 32, x * 64, y * 64); // 2x tile scale
      }
  }
}
