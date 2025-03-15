#include <stdio.h>
#include <SDL3/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "types.h"
#include "core/game.h"
#include "ui/menu.h"
#include "core/paddle.h"
#include "utils/render.h"

// Font file path - adjust this to the location of your font file
#define FONT_PATH "assets/fonts/OpenSans-Regular.ttf"
#define FONT_SIZE 24

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Pongy", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // Set window icon
    SDL_Surface* icon = create_icon();
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_DestroySurface(icon);
    }

    // Create renderer with vsync enabled for smoother animation
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Set renderer to use bilinear filtering for smoother scaling
    SDL_SetRenderVSync(renderer, 1);
    
    // Initialize font system
    if (!init_font(FONT_PATH, FONT_SIZE)) {
        printf("Warning: Font initialization failed. Using fallback text rendering.\n");
    }
    
    // Initialize game objects
    Paddle player1, player2;
    init_game(&player1, &player2);

    // Create menu buttons
    Button menu_buttons[3];
    init_menu_buttons(menu_buttons, 3);

    // Game state
    GameState current_state = STATE_MENU;
    
    // Mouse state
    float mouse_x = 0.0f, mouse_y = 0.0f;
    bool mouse_clicked = false;

    // Game loop variables
    bool running = true;
    SDL_Event event;
    Uint64 previous_time = SDL_GetTicks();
    const Uint64 frame_delay = 1000 / 60; // Target 60 FPS

    // Game loop
    while (running) {
        Uint64 frame_start = SDL_GetTicks();
        mouse_clicked = false;

        // Handle events
        running = handle_events(&event, &current_state, &mouse_x, &mouse_y, &mouse_clicked);

        // Update game state
        update_game_state(&current_state, menu_buttons, 3, &player1, &player2, mouse_x, mouse_y, mouse_clicked);
        
        // Check if user wants to exit
        if (current_state == STATE_EXIT) {
            running = false;
        }

        // Render game
        render_game(renderer, current_state, menu_buttons, 3, player1, player2);

        // Cap frame rate
        Uint64 frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    // Cleanup
    cleanup_font();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
} 