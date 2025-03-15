# Changelog

All notable changes to this project will be documented in this file.

## [0.5.0] - Text Rendering Improvements - 2023

### Added
- Proper text rendering using SDL_ttf library
- Open Sans font integration for all game text
- Font initialization and cleanup system
- Fallback rendering for when fonts aren't available
- Improved text appearance in menus and UI elements

## [0.4.0] - Code Refactoring - 2023

### Added
- Modular code structure with separation of concerns:
  - `types.h` - Common data structures and enums
  - `config.h` - Game constants and configuration
  - `game.h/game.c` - Game state management
  - `paddle.h/paddle.c` - Paddle mechanics
  - `menu.h/menu.c` - Menu system
  - `render.h/render.c` - Rendering utilities
- Improved maintainability and organization
- Better code reusability with encapsulated functions
- Enhanced build system with multiple source files in CMake

## [0.3.0] - Menu Implementation - 2023

### Added
- Main menu system with interactive buttons:
  - Start Game button to begin gameplay
  - Options button to access game settings
  - Exit button to quit the game
- Game state management for switching between different screens
- Mouse input handling with hover effects on buttons
- ESC key functionality to return to menu from gameplay
- Basic UI rendering system for menus and buttons
- Placeholder options screen

## [0.2.0] - Visual Improvements - 2023

### Added
- Custom window icon showing paddles and ball
- Center line divider with dashed styling
- Improved blue-tinted color scheme
- Smooth paddle movement with physics:
  - Acceleration and deceleration
  - Maximum speed cap
  - Momentum when moving
  - Boundary collision handling
- VSync rendering for smoother animation

## [0.1.2] - Control Refinement - 2023

### Fixed
- Fixed keyboard input handling to properly use SDL3's bool* return type from SDL_GetKeyboardState
- Correctly implemented paddle movement controls for both players

## [0.1.1] - Control Refinement - 2023

### Fixed
- Improved keyboard input detection by replacing SDL_GetKeyName with SDL_GetKeyboardState
- More responsive and reliable paddle controls for both players

## [0.1.0] - Initial Release - 2023

### Added
- Basic game window and rendering setup using SDL3
- Two-player control system
  - Player 1 (left paddle): W/S keys for up/down movement
  - Player 2 (right paddle): Up/Down arrow keys for movement
- Paddle physics with:
  - Smooth movement at constant speed (5 pixels per frame)
  - Collision detection with window boundaries
  - Proper positioning constraints to keep paddles on screen
- Game loop structure with:
  - 60 FPS frame rate cap for consistent gameplay
  - Clean event handling for keyboard input and window events
  - Proper resource cleanup on exit
- Minimalist black and white visual design
- Basic input handling:
  - Keyboard controls for both players
  - ESC key to exit the game
  - Window close button support

### Technical Implementation
- SDL3 initialization and configuration
- Window and renderer creation with error handling
- Game state management using C structures
- Consistent frame timing with SDL_Delay
- Memory management with proper cleanup routines

### Known Issues
- No ball or scoring system implemented yet
- No sound effects
- No menu system or game states

### What's Next
- Ball physics and collision detection
- Scoring system
- Sound effects for collisions and scoring
- Start menu and game states
- Single-player mode with AI opponent 