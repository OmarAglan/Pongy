# Pongy

A simple Pong-like game implemented in C using SDL3.

## Description

Pongy is a minimalist implementation of the classic Pong game. It features two paddles that can be controlled by keyboard inputs, allowing two players to compete against each other. The game includes a main menu system and proper text rendering.

## Features

- Two-player gameplay
- Smooth paddle movement with physics (acceleration, deceleration, momentum)
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

The game is still in development with the following features implemented:
- Main menu system with Start, Options, and Exit buttons
- Two-player paddle control with physics
- Custom blue-tinted visual theme with text rendering
- Proper game state management

## Future Improvements

- Add a ball with physics and collision detection
- Implement scoring system
- Add sound effects for collisions and scoring
- Add difficulty levels
- Add single-player mode with AI opponent
- Add more visual effects and animations

## License

This project is available under the MIT License.

## Acknowledgements

- SDL3 for providing the graphics library
- SDL3_ttf for text rendering
- Open Sans font
- The original Pong game for inspiration