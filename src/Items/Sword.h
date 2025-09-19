#ifndef SWORD_H
#define SWORD_H


#include "Item.h"
#include "../Entities/Player.h"

class Sword : public Item {
public:
    Sword () : Item("Sword", '/') { }

    std::string use (Player& player) override;
};


#endif //SWORD_H
