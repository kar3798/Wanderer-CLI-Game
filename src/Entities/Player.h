#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../Items/Item.h"
#include <map>
#include <memory>
#include <iostream>

class Player : public Entity {
public:

    Player(int x, int y);

    void update(Map& map) override;

    void addItem(std::unique_ptr<Item> item);
    std::string useItem(const std::string& name);
    void displayInventory() const;

    void heal(int amount);
    void increaseAttack(int amount);

    int getAttack() const {return attack; };
    int getHealth() const {return hp; };

private:
    std::map<std::string, std::unique_ptr<Item>> inventory;
    int attack = 10;
};

#endif //PLAYER_H
