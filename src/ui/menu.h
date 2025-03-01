#ifndef MENU_H
#define MENU_H

#include "../types.h"
#include <SDL3/SDL.h>

// Check if a point is inside a rectangle
bool is_point_in_rect(float x, float y, SDL_FRect rect);

// Draw a button
void draw_button(SDL_Renderer* renderer, Button button);

// Update button hover state
void update_button(Button* button, float mouse_x, float mouse_y);

// Draw the main menu
void draw_menu(SDL_Renderer* renderer, Button buttons[], int button_count);

// Initialize menu buttons
void init_menu_buttons(Button menu_buttons[], int count);

#endif // MENU_H 