cmake_minimum_required(VERSION 3.20)
project(Pongy)

set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL3_PATH "C:/SDL3")
set(SDL3_DIR "C:/SDL3/lib/cmake/SDL3")
list(APPEND CMAKE_PREFIX_PATH ${SDL3_PATH})

set(SDL3_INCLUDE_DIR "C:/SDL3/x86_64-w64-mingw32/include/SDL3")
include_directories(${SDL3_INCLUDE_DIR})

find_package(SDL3 REQUIRED)

add_executable(Pongy main.c)

target_include_directories(Pongy PRIVATE ${SDL3_INCLUDE_DIRS})
target_link_libraries(Pongy PRIVATE ${SDL3_LIBRARIES})
