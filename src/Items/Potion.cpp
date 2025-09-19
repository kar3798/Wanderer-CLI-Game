#include "Potion.h"

std::string Potion::use(Player& player) {
    player.heal(20);
    return "You used a potion and recovered 20 HP!";
}