#include "Enemy.h"
#include <iostream>
#include "../Utils/Logger.h"

Enemy::Enemy(int x, int y)
    : Entity(x, y, 'E', 50)
{ }

void Enemy::update() {
    // Placeholder for enemy logic (to be implemented in Phase 2)
    Logger::log("Enemy updated (no AI yet).");
}