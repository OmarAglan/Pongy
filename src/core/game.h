#ifndef GAME_H
#define GAME_H

#include "../types.h"
#include <SDL3/SDL.h>

// Initialize game objects
void init_game(Paddle* player1, Paddle* player2);

// Handle events and update game state
bool handle_events(SDL_Event* event, GameState* current_state, float* mouse_x, float* mouse_y, bool* mouse_clicked);

// Update game state based on current state
void update_game_state(GameState* current_state, Button menu_buttons[], int button_count, 
                       Paddle* player1, Paddle* player2, float mouse_x, float mouse_y, bool mouse_clicked);

// Render current game state
void render_game(SDL_Renderer* renderer, GameState current_state, Button menu_buttons[], int button_count,
                 Paddle player1, Paddle player2);

#endif // GAME_H 