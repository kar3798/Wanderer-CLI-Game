#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "../World/Map.h"

class Entity {
public:
    Entity(int x, int y, char symbol, int hp, int attack)
        : x(x), y(y), symbol(symbol), hp(hp), attack(attack) {}

    virtual ~Entity() = default;

    virtual void update(Map& map, class GameLoop& loop) = 0;

    virtual void render() const {
        std::cout << symbol;
    }

    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int newX, int newY) { x = newX; y = newY; }
    int getHP () const { return hp; }
    void takeDamage(int amount) { hp -= amount; }
    char getSymbol() const { return symbol; }
    int getAttack() const { return attack; }

protected:
    int x, y;
    char symbol;
    int hp;
    int attack;
};

#endif //ENTITY_H
