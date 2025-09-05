g++ -std=c++17 -I./src -I./src/Entities -I./src/Items -o Rougelike \
src/main.cpp \
src/Core/GameEngine.cpp \
src/Core/GameLoop.cpp \
src/World/Map.cpp \
src/World/Tile.cpp \
src/Utils/Logger.cpp \
src/Items/Potion.cpp

