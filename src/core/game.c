#include "game.h"
#include "../config.h"
#include "paddle.h"
#include "ball.h"
#include "../ui/menu.h"
#include "../utils/render.h"
#include <stdio.h>

// Initialize game objects
void init_game(Paddle* player1, Paddle* player2, Ball* ball, Score* score) {
    // Initialize player 1 paddle
    player1->rect.x = 20;
    player1->rect.y = WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2;
    player1->rect.w = PADDLE_WIDTH;
    player1->rect.h = PADDLE_HEIGHT;
    player1->velocity = 0;
    
    // Initialize player 2 paddle
    player2->rect.x = WINDOW_WIDTH - 40;
    player2->rect.y = WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2;
    player2->rect.w = PADDLE_WIDTH;
    player2->rect.h = PADDLE_HEIGHT;
    player2->velocity = 0;
    
    // Initialize the ball
    init_ball(ball);
    
    // Initialize score
    score->player1 = 0;
    score->player2 = 0;
}

// Handle events and update game state
bool handle_events(SDL_Event* event, GameState* current_state, float* mouse_x, float* mouse_y, bool* mouse_clicked) {
    bool running = true;
    
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event->key.scancode == SDL_SCANCODE_ESCAPE) {
                    if (*current_state == STATE_GAMEPLAY) {
                        *current_state = STATE_MENU;
                    } else if (*current_state == STATE_MENU) {
                        running = false;
                    }
                }
                break;
            case SDL_EVENT_MOUSE_MOTION:
                SDL_GetMouseState(mouse_x, mouse_y);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event->button.button == SDL_BUTTON_LEFT) {
                    *mouse_clicked = true;
                }
                break;
        }
    }
    
    return running;
}

// Update game state based on current state
void update_game_state(GameState* current_state, Button menu_buttons[], int button_count, 
                       Paddle* player1, Paddle* player2, Ball* ball, Score* score,
                       float mouse_x, float mouse_y, bool mouse_clicked) {
    switch (*current_state) {
        case STATE_MENU:
            // Update button states
            for (int i = 0; i < button_count; i++) {
                update_button(&menu_buttons[i], mouse_x, mouse_y);
                
                // Handle button clicks
                if (mouse_clicked && menu_buttons[i].hovered) {
                    switch (i) {
                        case 0: // Start Game
                            *current_state = STATE_GAMEPLAY;
                            // Reset game state when starting a new game
                            init_game(player1, player2, ball, score);
                            break;
                        case 1: // Options
                            *current_state = STATE_OPTIONS;
                            break;
                        case 2: // Exit
                            *current_state = STATE_EXIT;
                            break;
                    }
                }
            }
            break;
            
        case STATE_GAMEPLAY:
            {
                // Get keyboard state for both players
                int numkeys;
                const bool* keyboard_state = SDL_GetKeyboardState(&numkeys);
                
                // Access the keyboard state for the keys we're interested in
                bool p1_up = keyboard_state[SDL_SCANCODE_W];
                bool p1_down = keyboard_state[SDL_SCANCODE_S];
                bool p2_up = keyboard_state[SDL_SCANCODE_UP];
                bool p2_down = keyboard_state[SDL_SCANCODE_DOWN];
                
                // Update paddle positions
                handle_paddle_movement(player1, p1_up, p1_down);
                handle_paddle_movement(player2, p2_up, p2_down);
                
                // Update ball position and handle collisions
                int scored = update_ball(ball, player1, player2);
                
                // Handle scoring
                if (scored > 0) {
                    if (scored == 1) {
                        // Player 1 scored
                        score->player1++;
                        // Reset ball, sending it towards player 2
                        reset_ball(ball, 2);
                    } else if (scored == 2) {
                        // Player 2 scored
                        score->player2++;
                        // Reset ball, sending it towards player 1
                        reset_ball(ball, 1);
                    }
                }
            }
            break;
            
        case STATE_OPTIONS:
            // Currently, just a placeholder
            break;
            
        case STATE_EXIT:
            // Handled by main()
            break;
    }
}

// Render current game state
void render_game(SDL_Renderer* renderer, GameState current_state, Button menu_buttons[], int button_count,
                 Paddle player1, Paddle player2, Ball ball, Score score) {
    // Clear screen with background color
    SDL_SetRenderDrawColor(renderer, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, BACKGROUND_A);
    SDL_RenderClear(renderer);
    
    // Render based on game state
    switch (current_state) {
        case STATE_MENU:
            draw_menu(renderer, menu_buttons, button_count);
            break;
            
        case STATE_GAMEPLAY:
            // Draw center line
            draw_center_line(renderer);
            
            // Draw score
            char score_text[32];
            snprintf(score_text, sizeof(score_text), "%d    %d", score.player1, score.player2);
            SDL_FRect score_rect = {WINDOW_WIDTH/2.0f - 50.0f, 20.0f, 100.0f, 40.0f};
            draw_text(renderer, score_text, score_rect, 255, 255, 255, 255);
            
            // Draw paddles
            SDL_SetRenderDrawColor(renderer, PADDLE_R, PADDLE_G, PADDLE_B, PADDLE_A);
            SDL_RenderFillRect(renderer, &player1.rect);
            SDL_RenderFillRect(renderer, &player2.rect);
            
            // Draw ball
            draw_ball(renderer, ball);
            break;
            
        case STATE_OPTIONS:
            // Placeholder for options screen
            SDL_FRect options_rect = {WINDOW_WIDTH/4.0f, WINDOW_HEIGHT/2.0f, WINDOW_WIDTH/2.0f, 50.0f};
            draw_text(renderer, "Options Menu - Press ESC to return", 
                     options_rect,
                     BUTTON_TEXT_R, BUTTON_TEXT_G, BUTTON_TEXT_B, BUTTON_TEXT_A);
            break;
            
        case STATE_EXIT:
            // Nothing to render, game will exit
            break;
    }
    
    // Present renderer
    SDL_RenderPresent(renderer);
}