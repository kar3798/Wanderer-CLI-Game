#include "Player.h"
#include "../Utils/Logger.h"

Player::Player(int x, int y)
    : Entity(x, y, '@', 100)
{ }

void Player::update(Map& map) {

}

void Player::addItem(std::unique_ptr<Item> item) {
    std::string name = item->getName();
    inventory[name] = std::move(item);
    Logger::log("Player picked up: " + name);
}

std::string Player::useItem(const std::string& name) {
    if(inventory.count(name)) {
        std::string msg = inventory[name]->use((*this));
        inventory.erase(name);
        Logger::log("Player used: " + name);
        return msg;
    } else {
        Logger::log("Player tried to use missing item: " + name);
        return "You don't have a " + name + ".";
    }
}

void Player::displayInventory() const {
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

void Player::heal(int amount) {
    hp += amount;
    if (hp > 100) hp = 100;
    std::cout << "You healed " << amount << " HP. Current HP: " << hp << "\n";
    Logger::log("Player healed to " + std::to_string(hp) + " HP");
}

void Player::increaseAttack(int amount) {
    attack += amount;
    std::cout << "Your attack increased by " << amount
              << "! Current attack: " << attack << "\n";
    Logger::log("Player attack increased to " + std::to_string(attack));
}