#include "GameLoop.h"
#include "../Utils/Logger.h"
#include "../Items/Potion.h"
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

void GameLoop::start() {
    Logger::log("Game loop started.");
    printTitleArt();
    printLoadingBar();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Logger::log("Generating basic room.");
    map.generateBasicRoom();

    player = new Player(2, 2);
    entities.push_back(std::unique_ptr<Entity>(player));
    player->addItem(std::make_unique<Potion>());
    entities.push_back(std::make_unique<Enemy>(5, 2));


    while (isRunning){
        render();
        handleInput();
        updateWorld();
        processTurn();
    }
}

void GameLoop::render() {
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
    map.render(entities);
}

bool isWalkable(TileType type) {
    return type == TileType::Floor;
}

void GameLoop::handleInput() {

    std::cout << "[Input] Enter command (WASD to move, q to quit): ";
    std::string input;
    std::getline(std::cin, input);
    Logger::log("User input: " + input);

    int x = player->getX();
    int y = player->getY();
    if (input == "q") {
        isRunning = false;
    } else if (input == "w" || input == "W") {
        if (isWalkable(map.getTileType(x, y - 1))) {
            player->setPosition(x, y - 1);
            Logger::log("Player moved up (W)");
        }
    } else if (input == "s" || input == "S") {
        if (isWalkable(map.getTileType(x, y + 1))) {
            player->setPosition(x, y + 1);
            Logger::log("Player moved down (S)");
        }
    } else if (input == "a" || input == "A") {
        if (isWalkable(map.getTileType(x - 1, y))) {
            player->setPosition(x - 1, y);
            Logger::log("Player moved left (A)");
        }
    } else if (input == "d" || input == "D") {
        if (isWalkable(map.getTileType(x + 1, y))) {
            player->setPosition(x + 1, y);
            Logger::log("Player moved right (D)");
        }
    } else if (input == "use potion") {
        player->useItem("Potion");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } else if (input == "inventory") {
        player->displayInventory();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

}

void GameLoop::updateWorld() {
    Logger::log("Updating world state.");
    std::cout << "[Update] Updating the world state...\n";
}

void GameLoop::processTurn() {
    Logger::log("Processing turn.");
    std::cout << "[Turn] Processing player/enemy actions...\n";
}