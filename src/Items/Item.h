#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Player;

class Item {
public:
    Item(std::string name, char symbol) : name(std::move(name)), symbol(symbol) {}
    virtual ~Item() = default;

    virtual void use(Player& player) = 0;
    std::string getName() const { return name; }
    char getSymbol() const { return symbol; }

protected:
    std::string name;
    char symbol;
};

#endif //ITEM_H
