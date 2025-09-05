#ifndef KEY_H
#define KEY_H

#include "Item.h"
#include "../Entities/Player.h"

class Key : public Item {
public:
    Key() : Item("Key", 'k') { }

    void use (Player& player) override;
};


#endif //KEY_H
