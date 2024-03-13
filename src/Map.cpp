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
  std::ifstream mapFile(path);
  std::string line;
  std::vector<std::vector<int>> mapData;

  while (std::getline(mapFile, line)) {
      std::istringstream ss(line);
      std::vector<int> row;
      std::string value;

      while (std::getline(ss, value, ',')) {
          row.push_back(std::stoi(value));
      }

      mapData.push_back(row);
  }

  for (int y = 0; y < sizeY; ++y) {
      for (int x = 0; x < sizeX; ++x) {
          int tileCode = mapData[y][x];
          int srcX = tileCode % 10;
          int srcY = tileCode / 10;
          Game::AddTile(srcX * 32, srcY * 32, x * 32, y * 32);
      }
  }
}
