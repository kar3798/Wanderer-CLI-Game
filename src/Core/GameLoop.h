#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "../World/Map.h"
#include "../Utils/Logger.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"
#include "../Entities/Enemy.h"
#include <memory>
#include <vector>

class GameLoop {
public:
    void start();

private:
    void printTitleArt();
    void printLoadingBar();
    void render();
    void handleInput();
    void updateWorld();
    void processTurn();

    bool isRunning = true;

    Map map = Map(10, 5);

    std::vector<std::unique_ptr<Entity>> entities;
    Player* player = nullptr;

};

#endif //GAME_LOOP_H
