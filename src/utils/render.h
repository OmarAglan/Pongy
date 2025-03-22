#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>
#ifdef USE_SDL_TTF
#include "../../../SDL3/x86_64-w64-mingw32/include/SDL3_ttf/SDL_ttf.h"
#endif
#include <stdbool.h>

#ifdef USE_SDL_TTF
// Global font variable
extern TTF_Font* g_font;
#endif

// Initialize the font system
bool init_font(const char* font_path, int font_size);

// Clean up font resources
void cleanup_font();

// Draw text centered in a rectangle
void draw_text(SDL_Renderer* renderer, const char* text, SDL_FRect rect, int r, int g, int b, int a);

// Draw a dashed line in the center of the screen
void draw_center_line(SDL_Renderer* renderer);

// Create a simple 32x32 icon programmatically
SDL_Surface* create_icon();

#endif // RENDER_H