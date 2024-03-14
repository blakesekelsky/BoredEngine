#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Map {
  public:
    Map(std::string tId, int ms, int ts);
    ~Map();


    void AddTile(int srcX, int srcY, int x, int y);
    void LoadMapTiles(std::string path, int sizeX, int sizeY);
    void LoadMapCollisionTiles(std::string path, int sizeX, int sizeY);
  private:
    std::string texId;
    int tileSize;
    int mapScale;
    int scaledSize;
    std::vector<std::vector<int>> mapTileData;
    std::vector<std::vector<int>> mapCollisionData;
};

#endif