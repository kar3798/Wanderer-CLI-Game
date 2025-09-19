#include "Map.h"
#include "../Entities/Entity.h"
#include <iostream>

Map::Map(int width, int height) : width(width), height(height) {
    tiles.resize(height, std::vector<Tile>(width, Tile(TileType::Floor)));
}

void Map::generateBasicRoom() {
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            tiles[y][x] = Tile(TileType::Floor);
        }
    }

    for (int x = 0; x < width; ++x) {
        tiles[0][x] = Tile(TileType::Wall);
        tiles[height - 1][x] = Tile(TileType::Wall);
    }

    for (int y = 0; y < height; ++y) {
        tiles[y][0] = Tile(TileType::Wall);
        tiles[y][width - 1] = Tile(TileType::Wall);
    }
}

void Map::render(const std::vector<std::unique_ptr<Entity>> &entities) const {

    std::vector<std::vector<char>> display(height, std::vector<char>(width, '.'));

    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            if(tiles[y][x].getType() == TileType::Wall)
                display[y][x] = '#';

    for (const auto& entity : entities) {
        int x = entity->getX();
        int y = entity->getY();
        display[y][x] = entity->getSymbol();
    }

    for (const auto& row : display) {
        for (char ch : row)
            std::cout << ch;
        std::cout << '\n';
    }
}

TileType Map::getTileType(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y][x].getType();
    }
    return TileType::Wall;
}


