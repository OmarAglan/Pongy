#ifndef TYPES_H
#define TYPES_H

#include <SDL3/SDL.h>
#include <stdbool.h>

// Game states
typedef enum {
    STATE_MENU,
    STATE_GAMEPLAY,
    STATE_OPTIONS,
    STATE_EXIT
} GameState;

typedef struct {
    SDL_FRect rect;
    float velocity;
} Paddle;

typedef struct {
    SDL_FRect rect;
    const char* text;
    bool hovered;
} Button;

#endif // TYPES_H 