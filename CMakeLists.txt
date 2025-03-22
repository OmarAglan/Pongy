cmake_minimum_required(VERSION 3.20)
project(Pongy C)

set(CMAKE_C_STANDARD 17)

# SDL3 paths
set(SDL3_PATH "${CMAKE_SOURCE_DIR}/SDL3" CACHE PATH "Path to SDL3")
set(SDL3_DIR "${SDL3_PATH}/cmake" CACHE PATH "Path to SDL3 CMake config")
set(SDL3_INCLUDE_DIR "${SDL3_PATH}/x86_64-w64-mingw32/include" CACHE PATH "Path to SDL3 headers")

# SDL3_ttf paths
set(SDL3_TTF_PATH "${CMAKE_SOURCE_DIR}/SDL3" CACHE PATH "Path to SDL3_ttf")
set(SDL3_TTF_INCLUDE_DIR "${SDL3_TTF_PATH}/x86_64-w64-mingw32/include" CACHE PATH "Path to SDL3_ttf headers")
set(SDL3_TTF_LIB_DIR "${SDL3_TTF_PATH}/x86_64-w64-mingw32/lib" CACHE PATH "Path to SDL3_ttf libraries")

# Find SDL3
find_package(SDL3 REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${SDL3_INCLUDE_DIR})
include_directories(${SDL3_TTF_INCLUDE_DIR})

# Add compiler definitions for SDL_ttf
add_definitions(-DUSE_SDL_TTF)

# Source files
set(PONGY_SOURCES
    src/main.c
    src/core/game.c
    src/core/paddle.c
    src/core/ball.c
    src/ui/menu.c
    src/utils/render.c
)

# Create executable
add_executable(Pongy ${PONGY_SOURCES})

# Set the SDL3 and SDL3_ttf library paths
target_link_directories(Pongy PRIVATE ${SDL3_PATH}/x86_64-w64-mingw32/lib ${SDL3_TTF_LIB_DIR})

# Link libraries
target_link_libraries(Pongy PRIVATE SDL3::SDL3 SDL3_ttf)

# Copy DLLs to output directory (for Windows)
if(WIN32)
    add_custom_command(TARGET Pongy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_PATH}/x86_64-w64-mingw32/bin/SDL3.dll"
        $<TARGET_FILE_DIR:Pongy>
    )
    add_custom_command(TARGET Pongy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_TTF_PATH}/x86_64-w64-mingw32/bin/SDL3_ttf.dll"
        $<TARGET_FILE_DIR:Pongy>
    )
    
    # Copy assets directory to build directory
    add_custom_command(TARGET Pongy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Pongy>/assets"
    )
endif()
