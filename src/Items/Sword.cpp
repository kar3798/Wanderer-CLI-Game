#include "Sword.h"

std::string Sword::use(Player& player) {

    player.increaseAttack(5);
    return "You wield the sword! Your attack power increases.";
}