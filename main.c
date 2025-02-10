#include <stdio.h>
#include <SDL3/SDL.h>
#include <stdbool.h>

// Window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Paddle dimensions
#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 70
#define PADDLE_SPEED 5

typedef struct {
    SDL_FRect rect;
    float velocity;
} Paddle;

void handle_paddle_movement(Paddle* paddle, bool up_pressed, bool down_pressed) {
    if (up_pressed) {
        paddle->rect.y -= PADDLE_SPEED;
    }
    if (down_pressed) {
        paddle->rect.y += PADDLE_SPEED;
    }

    // Keep paddle within window bounds
    if (paddle->rect.y < 0) {
        paddle->rect.y = 0;
    }
    if (paddle->rect.y + paddle->rect.h > WINDOW_HEIGHT) {
        paddle->rect.y = WINDOW_HEIGHT - paddle->rect.h;
    }
}

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

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize game objects
    Paddle player1 = {
        .rect = {20, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT},
        .velocity = 0
    };
    
    Paddle player2 = {
        .rect = {WINDOW_WIDTH - 40, WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT},
        .velocity = 0
    };

    // Game loop variables
    bool running = true;
    SDL_Event event;
    Uint64 previous_time = SDL_GetTicks();
    const Uint64 frame_delay = 1000 / 60; // Target 60 FPS

    // Game loop
    while (running) {
        Uint64 frame_start = SDL_GetTicks();

        // Event handling
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                        running = false;
                    }
                    break;
            }
        }

        // Get keyboard state for both players
        bool p1_up = SDL_GetKeyName(SDL_SCANCODE_W);
        bool p1_down = SDL_GetKeyName(SDL_SCANCODE_S);
        bool p2_up = SDL_GetKeyName(SDL_SCANCODE_UP);
        bool p2_down = SDL_GetKeyName(SDL_SCANCODE_DOWN);

        // Update game state
        handle_paddle_movement(&player1, p1_up, p1_down);
        handle_paddle_movement(&player2, p2_up, p2_down);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw paddles
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player1.rect);
        SDL_RenderFillRect(renderer, &player2.rect);

        // Present renderer
        SDL_RenderPresent(renderer);

        // Cap frame rate
        Uint64 frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}