g++ -std=c++17 -I./src -I./src/Entities -I./src/Items -o Rougelike \
src/main.cpp \
src/Core/GameEngine.cpp \
src/Core/GameLoop.cpp \
src/Entities/Player.cpp \
src/Entities/Enemy.cpp \
src/World/Map.cpp \
src/World/Tile.cpp \
src/Utils/Logger.cpp \
src/Items/Potion.cpp \
src/Items/Sword.cpp \
src/Items/Key.cpp \
src/Utils/Input.cpp

