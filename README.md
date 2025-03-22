# Pongy

A simple Pong-like game implemented in C using SDL3.

## Description

Pongy is a minimalist implementation of the classic Pong game. It features two paddles that can be controlled by keyboard inputs, allowing two players to compete against each other. The game includes a main menu system, realistic ball physics, scoring, and proper text rendering.

## Features

- Two-player gameplay
- Smooth paddle movement with physics (acceleration, deceleration, momentum)
- Realistic ball physics with dynamic bouncing angles
- Progressive difficulty (ball speeds up with each hit)
- Scoring system with scoreboard display
- Ball bounces affected by paddle hit position and movement
- Main menu with Start, Options, and Exit buttons
- Proper text rendering using SDL_ttf and Open Sans font
- Custom window icon showing paddles and ball
- Center line divider with dashed styling
- Blue-tinted color scheme with hover effects
- 60 FPS gameplay with VSync for smoother animation
- Clean and modern interface

## Requirements

- C compiler (gcc, clang, etc.)
- SDL3 library
- SDL3_ttf library

## Installation

### Installing SDL3 and SDL3_ttf

Before compiling the game, you need to install the SDL3 and SDL3_ttf libraries:

#### Windows

1. Download SDL3 development libraries from the [SDL website](https://www.libsdl.org/)
2. Download SDL3_ttf development libraries from the [SDL_ttf website](https://github.com/libsdl-org/SDL_ttf)
3. Extract the files to a location on your system
4. Configure your compiler to include the SDL3 headers and link against the SDL3 and SDL3_ttf libraries

#### Linux

```bash
# Ubuntu/Debian
sudo apt-get install libsdl3-dev libsdl3-ttf-dev

# Fedora
sudo dnf install SDL3-devel SDL3_ttf-devel

# Arch Linux
sudo pacman -S sdl3 sdl3_ttf
```

#### macOS

```bash
brew install sdl3 sdl3_ttf
```

## Compilation

The project uses CMake for building. To compile:

```bash
mkdir build
cd build
cmake ..
make
```

## Running the Game

After compilation, run the executable:

```bash
./Pongy
```

## Controls

- **Menu Navigation**:
  - Mouse: Select and click buttons
  - ESC: Return to menu or exit

- **Player 1 (left paddle)**:
  - W: Move paddle up
  - S: Move paddle down

- **Player 2 (right paddle)**:
  - Up Arrow: Move paddle up
  - Down Arrow: Move paddle down

## Project Structure

- `src/` - Source code directory
  - `core/` - Core game mechanics
    - `game.c/h` - Game state management
    - `paddle.c/h` - Paddle mechanics
    - `ball.c/h` - Ball physics and collision
  - `ui/` - User interface components
    - `menu.c/h` - Menu system
  - `utils/` - Utility functions
    - `render.c/h` - Rendering utilities
  - `config.h` - Game constants and configuration
  - `types.h` - Common data structures and enums
  - `main.c` - Main game loop and initialization
- `assets/` - Game assets
  - `fonts/` - Font files (Open Sans)

## Current Development Status

The game is currently at version 0.9.0 with the following features implemented:
- Main menu system with Start, Options, and Exit buttons
- Proper text rendering using SDL_ttf
- Two-player paddle control with physics
- Ball physics with realistic bouncing and collisions
- Scoring system with on-screen display
- Dynamic difficulty (ball speeds up during gameplay)
- Custom blue-tinted visual theme
- Proper game state management

## Future Improvements

- Add sound effects for collisions and scoring using SDL_mixer
- Implement AI opponent for single-player mode
- Add power-ups and special gameplay modifiers
- Create additional game modes (challenge mode, time trial)
- Add win conditions and match tracking
- Enhance visuals with particle effects and animations
- Add settings menu for customization options

## License

This project is available under the MIT License.

## Acknowledgements

- SDL3 for providing the graphics library
- SDL3_ttf for text rendering
- Open Sans font
- The original Pong game for inspiration