# Pongy

A simple Pong-like game implemented in C using SDL3.

## Description

Pongy is a minimalist implementation of the classic Pong game. It features two paddles that can be controlled by keyboard inputs, allowing two players to compete against each other. The game includes a main menu system and proper text rendering.

## Features

- Two-player gameplay
- Smooth paddle movement with physics (acceleration, deceleration)
- Main menu with Start, Options, and Exit buttons
- Proper text rendering using SDL_ttf
- Custom window icon
- 60 FPS gameplay
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
  - `ui/` - User interface components
  - `utils/` - Utility functions
- `assets/` - Game assets
  - `fonts/` - Font files

## Future Improvements

- Add a ball with physics
- Implement scoring system
- Add sound effects
- Add difficulty levels
- Add single-player mode with AI

## License

This project is available under the MIT License.

## Acknowledgements

- SDL3 for providing the graphics library
- SDL3_ttf for text rendering
- Open Sans font
- The original Pong game for inspiration 