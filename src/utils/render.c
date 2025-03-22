#include "render.h"
#include "../config.h"
#include <string.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#ifdef USE_SDL_TTF
#include "../../../SDL3/x86_64-w64-mingw32/include/SDL3_ttf/SDL_ttf.h"
#endif

#ifdef USE_SDL_TTF
// Global font variable
TTF_Font* g_font = NULL;
#endif

// Initialize the font system
bool init_font(const char* font_path, int font_size) {
#ifdef USE_SDL_TTF
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    // Load font
    g_font = TTF_OpenFont(font_path, font_size);
    if (g_font == NULL) {
        printf("Failed to load font %s! SDL Error: %s\n", font_path, SDL_GetError());
        return false;
    }
    
    return true;
#else
    // SDL_ttf support is disabled
    printf("SDL_ttf support is disabled in this build.\n");
    return false;
#endif
}

// Clean up font resources
void cleanup_font() {
#ifdef USE_SDL_TTF
    // Free the font
    if (g_font != NULL) {
        TTF_CloseFont(g_font);
        g_font = NULL;
    }
    
    // Quit SDL_ttf
    TTF_Quit();
#endif
    // Nothing to clean up when SDL_ttf is disabled
}

// Draw text on the screen
void draw_text(SDL_Renderer* renderer, const char* text, SDL_FRect rect, int r, int g, int b, int a) {
#ifdef USE_SDL_TTF
    // If the font isn't loaded, fall back to rectangle rendering
    if (g_font == NULL) {
        printf("Warning: Font not initialized. Using fallback rendering.\n");
        // Use fallback rectangle rendering
        int text_width = (int)(strlen(text) * 10);
        int text_height = 20;
        
        SDL_FRect text_rect = {
            rect.x + (rect.w - text_width) / 2,
            rect.y + (rect.h - text_height) / 2,
            (float)text_width,
            (float)text_height
        };
        
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderFillRect(renderer, &text_rect);
        return;
    }
    
    // Create a surface from the text
    SDL_Color color = {r, g, b, a};
    // In SDL3_ttf, the function signature is different
    size_t text_length = strlen(text);
    SDL_Surface* text_surface = TTF_RenderText_Blended(g_font, text, text_length, color);
    if (text_surface == NULL) {
        printf("Unable to render text surface! SDL Error: %s\n", SDL_GetError());
        return;
    }
    
    // Create texture from surface
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (text_texture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_DestroySurface(text_surface);
        return;
    }
    
    // Get the dimensions of the texture
    int text_width = text_surface->w;
    int text_height = text_surface->h;
    
    // Free the surface as it's no longer needed
    SDL_DestroySurface(text_surface);
    
    // Set the destination rectangle for the text
    // Center the text within the provided rect
    SDL_FRect dest_rect = {
        rect.x + (rect.w - text_width) / 2,
        rect.y + (rect.h - text_height) / 2,
        (float)text_width,
        (float)text_height
    };
    
    // Render the text
    SDL_RenderTexture(renderer, text_texture, NULL, &dest_rect);
    
    // Free the texture
    SDL_DestroyTexture(text_texture);
#else
    // Fallback rectangle-based text rendering
    int text_width = (int)(strlen(text) * 10);
    int text_height = 20;
    
    SDL_FRect text_rect = {
        rect.x + (rect.w - text_width) / 2,
        rect.y + (rect.h - text_height) / 2,
        (float)text_width,
        (float)text_height
    };
    
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &text_rect);
#endif
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