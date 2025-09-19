#ifndef KEY_H
#define KEY_H

#include "Item.h"
#include "../Entities/Player.h"

class Key : public Item {
public:
    Key() : Item("Key", 'k') { }

    std::string use (Player& player) override;
};


#endif //KEY_H
