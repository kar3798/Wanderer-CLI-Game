#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "../World/Map.h"
#include "../Utils/Logger.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"
#include "../Entities/Enemy.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>

class GameLoop {
public:
    void start();

private:
    void printTitleArt();
    void printLoadingBar();
    void render();
    void addMessage(const std::string& msg);
    void movePlayer(int dx, int dy, const std::string& direction);
    int handleInput();
    void updateWorld();
    void processTurn();
    void renderInventory();
    void handleInventoryInput();

    bool isRunning = true;

    Map map = Map(10, 5);

    std::vector<std::unique_ptr<Entity>> entities;
    Player* player = nullptr;

    struct Command {
        std::function<void()> action;
        int turnCost;
    };

    std::unordered_map<std::string, Command> commands;
    std::vector<std::string> messageLog;

    enum class GameState {
        Playing,
        Inventory
    };

    GameState state = GameState::Playing;

};

#endif //GAME_LOOP_H
