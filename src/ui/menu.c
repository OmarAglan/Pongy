#include "menu.h"
#include "../config.h"
#include "../utils/render.h"
#include <string.h> // For strlen

// Check if a point is inside a rectangle
bool is_point_in_rect(float x, float y, SDL_FRect rect) {
    return (x >= rect.x && x < rect.x + rect.w &&
            y >= rect.y && y < rect.y + rect.h);
}

// Draw a button
void draw_button(SDL_Renderer* renderer, Button button) {
    // Draw button background
    if (button.hovered) {
        SDL_SetRenderDrawColor(renderer, BUTTON_HOVER_R, BUTTON_HOVER_G, BUTTON_HOVER_B, BUTTON_HOVER_A);
    } else {
        SDL_SetRenderDrawColor(renderer, BUTTON_NORMAL_R, BUTTON_NORMAL_G, BUTTON_NORMAL_B, BUTTON_NORMAL_A);
    }
    SDL_RenderFillRect(renderer, &button.rect);
    
    // Draw button border
    SDL_SetRenderDrawColor(renderer, BUTTON_TEXT_R, BUTTON_TEXT_G, BUTTON_TEXT_B, BUTTON_TEXT_A);
    SDL_RenderRect(renderer, &button.rect);
    
    // Draw button text
    draw_text(renderer, button.text, button.rect, BUTTON_TEXT_R, BUTTON_TEXT_G, BUTTON_TEXT_B, BUTTON_TEXT_A);
}

// Update button hover state
void update_button(Button* button, float mouse_x, float mouse_y) {
    button->hovered = is_point_in_rect(mouse_x, mouse_y, button->rect);
}

// Draw the main menu
void draw_menu(SDL_Renderer* renderer, Button buttons[], int button_count) {
    // Draw title
    SDL_FRect title_rect = {
        (WINDOW_WIDTH - 300) / 2.0f,
        (float)TITLE_PADDING,
        300.0f,
        60.0f
    };
    draw_text(renderer, "PONGY", title_rect, TITLE_R, TITLE_G, TITLE_B, TITLE_A);
    
    // Draw each button
    for (int i = 0; i < button_count; i++) {
        draw_button(renderer, buttons[i]);
    }
}

// Initialize menu buttons
void init_menu_buttons(Button menu_buttons[], int count) {
    if (count < 3) return; // Ensure we have enough buttons
    
    int button_y_start = WINDOW_HEIGHT / 2;
    
    // Start button
    menu_buttons[0].rect.x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2.0f;
    menu_buttons[0].rect.y = (float)button_y_start;
    menu_buttons[0].rect.w = (float)BUTTON_WIDTH;
    menu_buttons[0].rect.h = (float)BUTTON_HEIGHT;
    menu_buttons[0].text = "Start Game";
    menu_buttons[0].hovered = false;
    
    // Options button
    menu_buttons[1].rect.x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2.0f;
    menu_buttons[1].rect.y = (float)(button_y_start + BUTTON_HEIGHT + BUTTON_PADDING);
    menu_buttons[1].rect.w = (float)BUTTON_WIDTH;
    menu_buttons[1].rect.h = (float)BUTTON_HEIGHT;
    menu_buttons[1].text = "Options";
    menu_buttons[1].hovered = false;
    
    // Exit button
    menu_buttons[2].rect.x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2.0f;
    menu_buttons[2].rect.y = (float)(button_y_start + 2 * (BUTTON_HEIGHT + BUTTON_PADDING));
    menu_buttons[2].rect.w = (float)BUTTON_WIDTH;
    menu_buttons[2].rect.h = (float)BUTTON_HEIGHT;
    menu_buttons[2].text = "Exit";
    menu_buttons[2].hovered = false;
} 