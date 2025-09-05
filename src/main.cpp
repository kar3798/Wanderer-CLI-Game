#include <iostream>
#include "Core/GameEngine.h"

int main() {
    GameEngine engine;
    engine.init();
    std::cout << "Init done...\n";
    engine.run();
    std::cout << "Run finished...\n";
    engine.shutdown();
    return 0;
}
