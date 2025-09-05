#ifndef POTION_H
#define POTION_H

#include "Item.h"
#include "../Entities/Player.h"

class Potion : public Item {
public:
    Potion () : Item("Potion", '!') {}

    void use (Player& player) override;
};

#endif //POTION_H
