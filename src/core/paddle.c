#include "paddle.h"
#include "../config.h"
#include <math.h> // For fabsf

void handle_paddle_movement(Paddle* paddle, bool up_pressed, bool down_pressed) {
    // Apply acceleration based on input
    if (up_pressed) {
        paddle->velocity -= PADDLE_ACCELERATION;
    }
    if (down_pressed) {
        paddle->velocity += PADDLE_ACCELERATION;
    }
    
    // Cap maximum speed
    if (paddle->velocity > PADDLE_MAX_SPEED) {
        paddle->velocity = PADDLE_MAX_SPEED;
    } else if (paddle->velocity < -PADDLE_MAX_SPEED) {
        paddle->velocity = -PADDLE_MAX_SPEED;
    }
    
    // Apply velocity
    paddle->rect.y += paddle->velocity;
    
    // Apply deceleration when no keys are pressed or both keys are pressed
    if ((!up_pressed && !down_pressed) || (up_pressed && down_pressed)) {
        paddle->velocity *= PADDLE_DECELERATION;
    }
    
    // Stop completely if velocity is very small
    if (fabsf(paddle->velocity) < 0.1f) {
        paddle->velocity = 0;
    }

    // Keep paddle within window bounds
    if (paddle->rect.y < 0) {
        paddle->rect.y = 0;
        paddle->velocity = 0; // Stop at boundary
    }
    if (paddle->rect.y + paddle->rect.h > WINDOW_HEIGHT) {
        paddle->rect.y = WINDOW_HEIGHT - paddle->rect.h;
        paddle->velocity = 0; // Stop at boundary
    }
} 