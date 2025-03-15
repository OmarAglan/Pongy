#include "render.h"
#include "../config.h"
#include <string.h>
#include <stdio.h>

// Initialize the font - stub for future TTF implementation
bool init_font(const char* font_path, int font_size) {
    // SDL_ttf support is disabled
    printf("SDL_ttf support is disabled in this build.\n");
    return false;
}

// Clean up font resources - stub for future TTF implementation
void cleanup_font() {
    // Nothing to clean up when SDL_ttf is disabled
}

// Simulate text with a rectangle
void draw_text(SDL_Renderer* renderer, const char* text, SDL_FRect rect, int r, int g, int b, int a) {
    // Calculate approximate text dimensions based on string length
    int text_width = (int)(strlen(text) * 10);
    int text_height = 20;
    
    // Create a rectangle that represents the text
    SDL_FRect text_rect = {
        rect.x + (rect.w - text_width) / 2,
        rect.y + (rect.h - text_height) / 2,
        (float)text_width,
        (float)text_height
    };
    
    // Draw the text background
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &text_rect);
}

// Draw a dashed line in the center of the screen
void draw_center_line(SDL_Renderer* renderer) {
    // Set the line color
    SDL_SetRenderDrawColor(renderer, LINE_R, LINE_G, LINE_B, LINE_A);
    
    // Draw dashed line segments
    int dash_length = 10;
    int gap_length = 10;
    int x = WINDOW_WIDTH / 2;
    
    for (int y = 0; y < WINDOW_HEIGHT; y += dash_length + gap_length) {
        SDL_FRect dash = {
            (float)x - 1,
            (float)y,
            2.0f,
            (float)dash_length
        };
        SDL_RenderFillRect(renderer, &dash);
    }
}

// Create a simple icon for the window
SDL_Surface* create_icon() {
    // Create a 32x32 surface for the icon
    SDL_Surface* surface = SDL_CreateSurface(32, 32, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        printf("Failed to create icon surface: %s\n", SDL_GetError());
        return NULL;
    }
    
    // Fill the background
    SDL_FillSurfaceRect(surface, NULL, SDL_MapSurfaceRGBA(surface, 60, 60, 120, 255));
    
    // Draw left paddle
    SDL_Rect paddle = {5, 8, 6, 16};
    SDL_FillSurfaceRect(surface, &paddle, SDL_MapSurfaceRGBA(surface, 220, 220, 255, 255));
    
    // Draw right paddle
    paddle.x = 21;
    SDL_FillSurfaceRect(surface, &paddle, SDL_MapSurfaceRGBA(surface, 220, 220, 255, 255));
    
    // Draw a ball in the center
    SDL_Rect ball = {14, 14, 4, 4};
    SDL_FillSurfaceRect(surface, &ball, SDL_MapSurfaceRGBA(surface, 255, 255, 255, 255));
    
    return surface;
} 