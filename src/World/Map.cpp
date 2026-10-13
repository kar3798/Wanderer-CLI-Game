#include "Map.h"
#include "../Entities/Entity.h"
#include "../Utils/Logger.h"
#include <iostream>
#include <random>
#include <algorithm>

Map::Map(int width, int height) : width(width), height(height) {
    tiles.resize(height, std::vector<Tile>(width, Tile(TileType::Floor)));
}

bool Map::canPlaceRoom(const Room& room) const {
    for (const auto& existing : rooms) {
        if (room.intersects(existing)) {
            return false;
        }
    }
    return true;
}

void Map::carveRoom(const Room& room) {
    for (int y = room.y; y < room.y + room.height; ++y) {
        for (int x = room.x; x < room.x + room.width; ++x) {
            tiles[y][x] = Tile(TileType::Floor);
        }
    }
}

void Map::carveHorizontalCorridor(int x1, int x2, int y) {
    for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
        tiles[y][x] = Tile(TileType::Floor);
    }
}

void Map::carveVerticalCorridor(int y1, int y2, int x) {
    for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
        tiles[y][x] = Tile(TileType::Floor);
    }
}

void Map::carveCorridor(const Room& a, const Room& b) {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> coin(0, 1);

    int ax = a.getCenterX(), ay = a.getCenterY();
    int bx = b.getCenterX(), by = b.getCenterY();

    if (coin(rng) == 0) {
        carveHorizontalCorridor(ax, bx, ay);
        carveVerticalCorridor(ay, by, bx);
    } else {
        carveVerticalCorridor(ay, by, ax);
        carveHorizontalCorridor(ax, bx, by);
    }
}

void Map::generateDungeon(int roomCount, int minRoomSize, int maxRoomSize) {
    // Start from solid rock; rooms and corridors carve Floor into it.
    tiles.assign(height, std::vector<Tile>(width, Tile(TileType::Wall)));
    rooms.clear();

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> sizeDist(minRoomSize, maxRoomSize);

    int attempts = 0;
    const int maxAttempts = roomCount * 20;

    while (static_cast<int>(rooms.size()) < roomCount && attempts < maxAttempts) {
        ++attempts;

        int w = sizeDist(rng);
        int h = sizeDist(rng);
        if (w > width - 2 || h > height - 2) {
            continue; // wouldn't fit inside the map border, try a different size
        }

        std::uniform_int_distribution<int> xDist(1, width - w - 1);
        std::uniform_int_distribution<int> yDist(1, height - h - 1);
        Room candidate{ xDist(rng), yDist(rng), w, h };

        if (!canPlaceRoom(candidate)) {
            continue; // overlaps an existing room, discard and retry
        }

        carveRoom(candidate);
        if (!rooms.empty()) {
            carveCorridor(rooms.back(), candidate); // connect to the previous room
        }
        rooms.push_back(candidate);
    }

    if (rooms.empty()) {
        // Degenerate fallback so the game never has zero walkable tiles.
        Logger::log("Dungeon generation placed 0 rooms; falling back to single room.");
        Room fallback{1, 1, width - 2, height - 2};
        carveRoom(fallback);
        rooms.push_back(fallback);
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


