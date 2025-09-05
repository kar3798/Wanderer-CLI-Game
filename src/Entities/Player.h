#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../Items/Item.h"
#include <map>
#include <memory>
#include <iostream>

class Player : public Entity {
public:
    Player(int x, int y) : Entity(x, y, '@', 100) {}

    void update() override {
        // Movement or player-specific logic will go here
    }

    void addItem(std::unique_ptr<Item> item) {
        std::string name = item->getName();
        inventory[name] = std::move(item);
    }

    void useItem(const std::string& name) {
        if(inventory.count(name)) {
            inventory[name]->use((*this));
            inventory.erase(name);
        } else {
            std::cout << "You don't have a " << name << ".\n";
        }
    }

    void heal(int amount) {
        hp += amount;
        if (hp > 100)
            hp = 100;
    }

    void displayInventory() const {
        std::cout << "\n=== Inventory ===\n";
        if (inventory.empty()) {
            std::cout << "(empty)\n";
        } else {
            for (const auto& [name, item] : inventory) {
                std::cout << "- " << name << " [" << item->getSymbol() << "]\n";
            }
        }
        std::cout << "=================\n";
    }


private:
    std::map<std::string, std::unique_ptr<Item>> inventory;
};

#endif //PLAYER_H
