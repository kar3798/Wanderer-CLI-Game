#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <vector>
#include <memory>

class Entity;

class Map {
public:
    Map(int width, int height);
    void generateBasicRoom();
    void render(const std::vector<std::unique_ptr<Entity>> &entities) const;
    TileType getTileType(int x, int y) const;


private:
    int width, height;
    std::vector<std::vector<Tile>> tiles;
};

#endif //MAP_H
