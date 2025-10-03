#include "GameLoop.h"
#include "../Utils/Logger.h"
#include "../Items/Potion.h"
#include "../Items/Sword.h"
#include "../Items/Key.h"
#include "../Utils/Input.h"
#include <iostream>
#include <chrono>
#include <thread>


void GameLoop::printTitleArt() {
    std::cout << R"(
 _    _                 _
| |  | |               | |
| |  | | __ _ _ __   __| | ___ _ __ ___ _ __
| |/\| |/ _` | '_ \ / _` |/ _ \ '__/ _ \ '__|
\  /\  / (_| | | | | (_| |  __/ | |  __/ |
 \/  \/ \__,_|_| |_|\__,_|\___|_|  \___|_|

    A Rouge-lite Terminal Dungeon Crawler Adventure 𓆝 𓆟 𓆞 𓆝 𓆟
)" << "\n\n";
}

void GameLoop::printLoadingBar() {
    std::cout << "\n Loading: [";
    std::cout.flush();

    const int total = 50;
    for (int i = 0; i < total; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "#";
        std::cout.flush();
    }

    std::cout << "] Done!\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void GameLoop::render() {
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
    map.render(entities);

    std::cout << "\n--- Messages ---\n";
    for (const auto& msg : messageLog) {
        std::cout << msg << "\n";
    }
    std::cout << "----------------\n";
}

bool isWalkable(TileType type) {
    return type == TileType::Floor;
}

void GameLoop::addMessage(const std::string& msg) {
    messageLog.push_back(msg);
    if (messageLog.size() > 5) {
        messageLog.erase(messageLog.begin());
    }
}

void GameLoop::movePlayer(int dx, int dy, const std::string &direction) {
    int x = player->getX();
    int y = player->getY();
    if (isWalkable(map.getTileType(x + dx, y + dy))) {
        player->setPosition(x + dx, y + dy);
        addMessage("Player moved " + direction);
        Logger::log("Player moved " + direction);
    }
}

int GameLoop::handleInput() {

    std::cout << "[Input] Enter command (WASD to move, q to quit): ";
    char ch = getCharInput();
    std::string input(1, ch);
    Logger::log("User input: " + input);

    if (commands.count(input)) {
        commands[input].action();
        return commands[input].turnCost;
        }
    else {
        std::cout << "Unknown command.\n";
        return 0;
    }

}

void GameLoop::updateWorld() {
    Logger::log("Updating world state.");
    std::cout << "[Update] Updating the world state...\n";
}

void GameLoop::processTurn() {
    Logger::log("Processing turn.");

    for (auto& e : entities) {
        e->update(map);
    }
}

void GameLoop::renderInventory() {
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
    player->displayInventory();
    std::cout << "\nPress [q] to return to the game.\n";
}

void GameLoop::handleInventoryInput() {
    char ch = getCharInput();
    std::string input(1, ch);

    if (input == "q" || input == "Q") {
        state = GameState::Playing;
    }
}


void GameLoop::start() {
    Logger::log("Game loop started.");
    printTitleArt();
//    printLoadingBar();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Logger::log("Generating basic room.");
    map.generateBasicRoom();

    player = new Player(2, 2);
    entities.push_back(std::unique_ptr<Entity>(player));

    // Adding starting items
    player->addItem(std::make_unique<Potion>());
    player->addItem(std::make_unique<Sword>());
    player->addItem(std::make_unique<Key>());

    // Spawn enemy
    entities.push_back(std::make_unique<Enemy>(5, 2));

    // Commands
    commands["w"] = { [this]() { movePlayer(0, -1, "up (W)"); }, 1 };
    commands["s"] = { [this]() { movePlayer(0, 1, "down (S)"); }, 1 };
    commands["a"] = { [this]() { movePlayer(-1, 0, "left (A)"); }, 1 };
    commands["d"] = { [this]() { movePlayer(1, 0, "right (D)"); }, 1 };

    commands["p"] = { [this]() { addMessage(player->useItem("Potion")); }, 3 };
    commands["S"]  = { [this]() { addMessage(player->useItem("Sword")); }, 2 };
    commands["k"]    = { [this]() { addMessage(player->useItem("Key")); }, 2 };

    commands["i"] = { [this]() { state = GameState::Inventory; }, 0 };

    commands["q"] = { [this]() { isRunning = false; }, 0 };

    while (isRunning){
        render();
        if (state == GameState::Playing) {
            int turns = handleInput();
            for (int i = 0; i < turns; ++i) {
                updateWorld();
                processTurn();
            }
        }
        else if (state == GameState::Inventory) {
            renderInventory();
            handleInventoryInput();
        }
    }
}





