#include "Enemy.h"
#include <random>
#include "../Utils/Logger.h"

// Create a global random engine for the whole program
static std::mt19937 rng(std::random_device{}());

Enemy::Enemy(int x, int y)
    : Entity(x, y, 'E', 50)
{ }

void Enemy::update(Map& map) {
    // Uniform distribution between 0 and 3
    static std::uniform_int_distribution<int> dist(0, 3);

    int dx = 0, dy = 0;
    int dir = dist(rng); // 0-3 assigned randomly

    switch (dir) {
        case 0: dy = -1; break; // up
        case 1: dy = 1;  break; // down
        case 2: dx = -1; break; // left
        case 3: dx = 1;  break; // right
    }

    int newX = getX() + dx;
    int newY = getY() + dy;

    if (map.getTileType(newX, newY) == TileType::Floor) {
        setPosition(newX, newY);
        Logger::log("Enemy moved.");
    }
}