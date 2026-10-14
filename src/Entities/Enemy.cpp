#include "Enemy.h"
#include <random>
#include <cstdlib>
#include "../Utils/Logger.h"
#include "../Core/GameLoop.h"

// Create a global random engine for the whole program
static std::mt19937 rng(std::random_device{}());
static std::uniform_int_distribution<int> dist(0, 3);

Enemy::Enemy(int x, int y)
    : Entity(x, y, 'E', 50, 5)
{ }

void Enemy::update(Map& map, GameLoop& loop) {
    Player& player = loop.getPlayer();
    int distance = std::abs(player.getX() - getX()) + std::abs(player.getY() - getY());
    if (distance == 1) {
        player.takeDamage(attack);
        loop.addMessage("The enemy hits you for " + std::to_string(attack) + " damage!");
        Logger::log("Enemy attacked player for " + std::to_string(attack));
        return;
    }

    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, 3);

    int dx = 0, dy = 0;
    int tries = 0;
    bool moved = false;

    while (!moved && tries < 4) {
        int dir = dist(rng); // random direction
        dx = dy = 0;

        switch (dir) {
            case 0: dy = -1; break; // up
            case 1: dy =  1; break; // down
            case 2: dx = -1; break; // left
            case 3: dx =  1; break; // right
        }

        int newX = getX() + dx;
        int newY = getY() + dy;

        // Check bounds before moving
        if (newX >= 0 && newY >= 0 &&
            newX < map.getWidth() && newY < map.getHeight() &&
            map.getTileType(newX, newY) == TileType::Floor &&
            !loop.isEntityAt(newX, newY, this))
        {
            setPosition(newX, newY);
            moved = true;
            Logger::log("Enemy moved.");
        }

        ++tries;
    }

    if (!moved) {
        Logger::log("Enemy did not move (blocked or at edge).");
    }
}
