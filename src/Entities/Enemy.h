#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <iostream>

class Enemy : public Entity{
public:
    Enemy(int x, int y) : Entity(x, y, 'E', 50) {}

    void update() override {
        // Implement later
    }
};

#endif //ENEMY_H
