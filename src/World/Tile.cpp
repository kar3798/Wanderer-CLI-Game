#include "Tile.h"

Tile::Tile(TileType type) : type(type) {}

char Tile::getDisplayChar() const {
    switch (type) {
        case TileType::Wall: return '#';
        case TileType::Floor: return '.';
        default: return '?';
    }
}

TileType Tile::getType() const {
    return type;
}
