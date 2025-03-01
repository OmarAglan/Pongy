cmake_minimum_required(VERSION 3.20)
project(Pongy C)

set(CMAKE_C_STANDARD 17)

# SDL3 paths
set(SDL3_PATH "C:/SDL3" CACHE PATH "Path to SDL3")
set(SDL3_DIR "${SDL3_PATH}/cmake" CACHE PATH "Path to SDL3 CMake config")
set(SDL3_INCLUDE_DIR "${SDL3_PATH}/include" CACHE PATH "Path to SDL3 headers")

# Find SDL3
find_package(SDL3 REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${SDL3_INCLUDE_DIR})

# Source files
set(PONGY_SOURCES
    src/main.c
    src/core/game.c
    src/core/paddle.c
    src/ui/menu.c
    src/utils/render.c
)

# Create executable
add_executable(Pongy ${PONGY_SOURCES})

# Link libraries
target_link_libraries(Pongy PRIVATE SDL3::SDL3)
