#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

class Entity {
public:
    Entity(int x, int y, char symbol, int hp)
        : x(x), y(y), symbol(symbol), hp(hp) {}

    virtual ~Entity() = default;

    virtual void update() = 0;

    virtual void render() const {
        std::cout << symbol;
    }

    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int newX, int newY) { x = newX; y = newY; }
    int getHP () const { return hp; }
    void takeDamage(int amount) { hp -= amount; }
    char getSymbol() const { return symbol; }

protected:
    int x, y;
    char symbol;
    int hp;
};

#endif //ENTITY_H
