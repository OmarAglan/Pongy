cmake_minimum_required(VERSION 3.28)
project(Pongy C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL3_PATH "${CMAKE_SOURCE_DIR}/SDL3/x86_64-w64-mingw32")
set(SDL3_INCLUDE_DIRS "${SDL3_PATH}/include")

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

add_executable(Pongy main.c)

target_link_libraries(${PROJECT_NAME} ${SDL3_LIBRARY})
