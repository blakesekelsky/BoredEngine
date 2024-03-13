#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
  public:
    Map();
    ~Map();

    static void LoadMap(std::string path, int sizeX, int sizeY);
  private:
    
};

#endif