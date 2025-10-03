#include "GameEngine.h"
#include <cstdlib>
#include <ctime>


void GameEngine::init() {
    Logger::init("game.log");
    Logger::log("Initializing Game Engine.");
    std::cout << "Initializing Game Engine...\n";
    srand(static_cast<unsigned>(time(nullptr))); // seed for random number generator
    gameLoop = std::make_unique<GameLoop>();
}

void GameEngine::run() {
    if(gameLoop){
        Logger::log("Game Started.");
        gameLoop->start();
    }
}

void GameEngine::shutdown() {
    Logger::log("Shutting down Game Engine.");
    std::cout << "Shutting down Game Engine.\n";
    Logger::shutdown();
}