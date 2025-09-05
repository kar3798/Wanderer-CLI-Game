#include "Potion.h"

void Potion::use(Player& player) {
    std::cout << "You used a potion and recovered 20 HP!\n";
    player.heal(20);
}