#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <iostream>

class Enemy : public Entity{
public:
    Enemy(int x, int y);

    void update(Map& map, GameLoop& loop) override;

    // Enemy suggest its next move; GameLoop will decide if it's valid
    std::pair<int, int> getNextMove(Map& map);
};

#endif //ENEMY_H
