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

bool GameLoop::isEntityAt(int x, int y, Entity* exclude) {
    for (auto& e : entities) {
        if (e.get() != exclude && e->getX() == x && e->getY() == y) {
            return true;
        }
    }
    return false;
}

void GameLoop::movePlayer(int dx, int dy, const std::string &direction) {
    int x = player->getX();
    int y = player->getY();
    if (isWalkable(map.getTileType(x + dx, y + dy))
    && !isEntityAt(x + dx, y + dy, player)) {
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
        e->update(map, *this);
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

void GameLoop::playerAttack(int dx, int dy) {
    int px = player->getX();
    int py = player->getY();

    // check all 4 adjacent tiles
    std::vector<std::pair<int,int>> directions = {
            {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };

    bool attacked = false;

    for (auto dir : directions) {
        int tx = px + dir.first;
        int ty = py + dir.second;

        for (auto it = entities.begin(); it != entities.end(); ++it) {
            Enemy* enemy = dynamic_cast<Enemy*>(it->get());
            if (enemy && enemy->getX() == tx && enemy->getY() == ty) {
                int dmg = player->getAttack();
                enemy->takeDamage(dmg);
                addMessage("You hit the enemy for " + std::to_string(player->getAttack()) + " damage!");

                if (enemy->getHP() <= 0) {
                    addMessage("Enemy died!");
                    entities.erase(it); // removing dead enemy
                }
                attacked = true;
                break; // stop after hitting one enemy in that direction
            }
        }
        if (attacked) break; // only one attack per action
    }
    if (!attacked) {
        addMessage("No enemy nearby to attack!");
    }
}

void GameLoop::start() {
    Logger::log("Game loop started.");
    printTitleArt();
    printLoadingBar();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Logger::log("Generating dungeon.");
    map.generateDungeon();

    const auto& rooms = map.getRooms();

    // Player spawns in the first generated room.
    int playerX = rooms[0].getCenterX();
    int playerY = rooms[0].getCenterY();
    player = new Player(playerX, playerY);
    entities.push_back(std::unique_ptr<Entity>(player));

    // Adding starting items
    player->addItem(std::make_unique<Potion>());
    player->addItem(std::make_unique<Sword>());
    player->addItem(std::make_unique<Key>());

    // Enemy spawns in a different room when one exists, so it isn't next to the player.
    int enemyRoomIndex = (rooms.size() > 1) ? 1 : 0;
    int enemyX = rooms[enemyRoomIndex].getCenterX();
    int enemyY = rooms[enemyRoomIndex].getCenterY();

    // Only reachable if generation degenerated to a single room: nudge off the player's tile.
    if (enemyX == playerX && enemyY == playerY) {
        enemyX += 1;
        if (map.getTileType(enemyX, enemyY) != TileType::Floor) {
            enemyX -= 2;
        }
    }

    entities.push_back(std::make_unique<Enemy>(enemyX, enemyY));

    // Commands
    // Character Movement
    commands["w"] = { [this]() { movePlayer(0, -1, "up (W)"); }, 1 };
    commands["s"] = { [this]() { movePlayer(0, 1, "down (S)"); }, 1 };
    commands["a"] = { [this]() { movePlayer(-1, 0, "left (A)"); }, 1 };
    commands["d"] = { [this]() { movePlayer(1, 0, "right (D)"); }, 1 };

    // Combat Actions
    commands["1"] = { [this]() { addMessage(player->useItem("Potion")); }, 3 };
    commands["2"] = { [this]() { addMessage(player->useItem("Sword")); }, 2 };
    commands["3"] = { [this]() { addMessage(player->useItem("Key")); }, 2 };

    commands["W"] = { [this]() { playerAttack(0, -1);}, 1};
    commands["A"] = { [this]() { playerAttack(0, 1);}, 1};
    commands["S"] = { [this]() { playerAttack(-1, 0);}, 1};
    commands["D"] = { [this]() { playerAttack(1, 0);}, 1};

    // Inventory
    commands["i"] = { [this]() { state = GameState::Inventory; }, 0 };

    // Quit
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





