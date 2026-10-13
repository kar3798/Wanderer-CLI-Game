#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "Room.h"
#include <vector>
#include <memory>

class Entity;

class Map {
public:
    Map(int width, int height);
    void generateDungeon(int roomCount = 6, int minRoomSize = 4, int maxRoomSize = 8);
    void render(const std::vector<std::unique_ptr<Entity>> &entities) const;
    TileType getTileType(int x, int y) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    const std::vector<Room>& getRooms() const { return rooms; }


private:
    bool canPlaceRoom(const Room& room) const;
    void carveRoom(const Room& room);
    void carveCorridor(const Room& a, const Room& b);
    void carveHorizontalCorridor(int x1, int x2, int y);
    void carveVerticalCorridor(int y1, int y2, int x);

    int width, height;
    std::vector<std::vector<Tile>> tiles;
    std::vector<Room> rooms;
};

#endif //MAP_H
