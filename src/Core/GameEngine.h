
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <memory>
#include "GameLoop.h"

class GameLoop;

class GameEngine {
public:
    void init();
    void run();
    void shutdown();

private:
    std::unique_ptr<GameLoop> gameLoop;
};

#endif //GAME_ENGINE_H
