#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Map {
  public:
    Map(const char *mfp, int ms, int ts);
    ~Map();


    void AddTile(int srcX, int srcY, int x, int y);
    void LoadMapTiles(std::string path, int sizeX, int sizeY);
    void LoadMapCollisionTiles(std::string path, int sizeX, int sizeY);
  private:
    const char *mapfilePath;
    int tileSize;
    int mapScale;
    int scaledSize;
    std::vector<std::vector<int>> mapTileData;
    std::vector<std::vector<int>> mapCollisionData;
};

#endif