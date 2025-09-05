#ifndef TILE_H
#define TILE_H

enum class TileType {
    Wall,
    Floor
};

class Tile {
public:
    Tile(TileType type);
    char getDisplayChar() const;
    TileType getType() const;


private:
    TileType type;
};

#endif //TILE_H
