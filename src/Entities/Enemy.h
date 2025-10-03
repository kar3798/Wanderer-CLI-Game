#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <iostream>

class Enemy : public Entity{
public:
    Enemy(int x, int y);

    void update(Map& map) override;
};

#endif //ENEMY_H
