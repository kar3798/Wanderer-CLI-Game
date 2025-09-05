cmake_minimum_required(VERSION 3.27)
project(Rougelike)

set(CMAKE_CXX_STANDARD 17)

# Collect all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

# Add executable
add_executable(Rougelike ${SOURCES} ${HEADERS})

