#include "ball.h"
#include "../config.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Initialize ball with default values
void init_ball(Ball* ball) {
    // Set initial position to center of screen
    ball->rect.x = WINDOW_WIDTH / 2.0f - BALL_SIZE / 2.0f;
    ball->rect.y = WINDOW_HEIGHT / 2.0f - BALL_SIZE / 2.0f;
    ball->rect.w = BALL_SIZE;
    ball->rect.h = BALL_SIZE;
    
    // Seed random number generator
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }
    
    // Set initial velocity (random direction)
    ball->base_speed = BALL_INITIAL_SPEED;
    ball->speed_increment = 0.0f;
    
    // Random angle between -45 and 45 degrees or 135 and 225 degrees
    // (ensures the ball moves horizontally at first)
    float angle;
    if (rand() % 2 == 0) {
        // Right direction
        angle = ((float)(rand() % 90) - 45.0f) * M_PI / 180.0f;
    } else {
        // Left direction
        angle = ((float)(rand() % 90) + 135.0f) * M_PI / 180.0f;
    }
    
    float speed = ball->base_speed;
    ball->velocity_x = speed * cosf(angle);
    ball->velocity_y = speed * sinf(angle);
    
    // No player has hit the ball yet
    ball->last_hit_by = 0;
}

// Update ball position and handle collisions
int update_ball(Ball* ball, Paddle* player1, Paddle* player2) {
    // Apply velocity
    ball->rect.x += ball->velocity_x;
    ball->rect.y += ball->velocity_y;
    
    // Handle wall collisions (top and bottom)
    if (ball->rect.y <= 0) {
        ball->rect.y = 0;
        ball->velocity_y = -ball->velocity_y;
        
        // Add slight variation to prevent the ball from getting stuck
        if (fabsf(ball->velocity_y) < 2.0f) {
            ball->velocity_y += (rand() % 100) / 100.0f;
        }
    } else if (ball->rect.y + ball->rect.h >= WINDOW_HEIGHT) {
        ball->rect.y = WINDOW_HEIGHT - ball->rect.h;
        ball->velocity_y = -ball->velocity_y;
        
        // Add slight variation to prevent the ball from getting stuck
        if (fabsf(ball->velocity_y) < 2.0f) {
            ball->velocity_y -= (rand() % 100) / 100.0f;
        }
    }
    
    // Check for scoring (left and right walls)
    if (ball->rect.x + ball->rect.w < 0) {
        // Player 2 scores
        return 2;
    } else if (ball->rect.x > WINDOW_WIDTH) {
        // Player 1 scores
        return 1;
    }
    
    // Check for paddle collisions
    if (check_paddle_collision(ball, player1, 1)) {
        // Speed up slightly with each hit
        ball->speed_increment += BALL_SPEEDUP_FACTOR;
        
        // Cap the speed increment
        if (ball->speed_increment > BALL_MAX_SPEEDUP) {
            ball->speed_increment = BALL_MAX_SPEEDUP;
        }
    } else if (check_paddle_collision(ball, player2, 2)) {
        // Speed up slightly with each hit
        ball->speed_increment += BALL_SPEEDUP_FACTOR;
        
        // Cap the speed increment
        if (ball->speed_increment > BALL_MAX_SPEEDUP) {
            ball->speed_increment = BALL_MAX_SPEEDUP;
        }
    }
    
    return 0; // No scoring
}

// Check if the ball collides with a paddle
bool check_paddle_collision(Ball* ball, Paddle* paddle, int paddle_id) {
    // Simple AABB collision detection
    if (ball->rect.x < paddle->rect.x + paddle->rect.w &&
        ball->rect.x + ball->rect.w > paddle->rect.x &&
        ball->rect.y < paddle->rect.y + paddle->rect.h &&
        ball->rect.y + ball->rect.h > paddle->rect.y) {
        
        // Ball is colliding with paddle
        
        // Don't register another collision if the ball was already hit by this paddle
        if (ball->last_hit_by == paddle_id) {
            return false;
        }
        
        // Record which paddle hit the ball
        ball->last_hit_by = paddle_id;
        
        // Calculate where on the paddle the ball hit (0.0 = top, 1.0 = bottom)
        float hit_position = (ball->rect.y + ball->rect.h/2 - paddle->rect.y) / paddle->rect.h;
        
        // Constrain hit_position between 0 and 1
        if (hit_position < 0.0f) hit_position = 0.0f;
        if (hit_position > 1.0f) hit_position = 1.0f;
        
        // Calculate new angle based on hit position
        // Center hit (0.5) = horizontal reflection
        // Edge hits = more extreme angles
        float angle_factor = (hit_position - 0.5f) * BALL_MAX_BOUNCE_ANGLE;
        
        // Calculate new velocity based on angle
        float speed = ball->base_speed + ball->speed_increment;
        
        // Adjust angle based on which paddle was hit
        if (paddle_id == 1) {
            // Right-facing angle
            ball->velocity_x = fabsf(speed * cosf(angle_factor));
            ball->velocity_y = speed * sinf(angle_factor);
        } else {
            // Left-facing angle
            ball->velocity_x = -fabsf(speed * cosf(angle_factor));
            ball->velocity_y = speed * sinf(angle_factor);
        }
        
        // Add some of the paddle's momentum to the ball
        ball->velocity_y += paddle->velocity * BALL_PADDLE_INFLUENCE;
        
        // Ensure the ball doesn't get stuck inside the paddle
        if (paddle_id == 1) {
            ball->rect.x = paddle->rect.x + paddle->rect.w;
        } else {
            ball->rect.x = paddle->rect.x - ball->rect.w;
        }
        
        return true;
    }
    
    return false;
}

// Reset the ball to the center after scoring
void reset_ball(Ball* ball, int scored_by) {
    // Reset position to center
    ball->rect.x = WINDOW_WIDTH / 2.0f - BALL_SIZE / 2.0f;
    ball->rect.y = WINDOW_HEIGHT / 2.0f - BALL_SIZE / 2.0f;
    
    // Reset base speed (keep some of the speedup for difficulty progression)
    ball->speed_increment *= BALL_SPEEDUP_RETENTION;
    
    // Set velocity in direction of the player who just got scored on
    float angle;
    if (scored_by == 1) {
        // Ball goes towards player 1 (left)
        angle = ((float)(rand() % 60) - 30.0f + 180.0f) * M_PI / 180.0f;
    } else {
        // Ball goes towards player 2 (right)
        angle = ((float)(rand() % 60) - 30.0f) * M_PI / 180.0f;
    }
    
    float speed = ball->base_speed + ball->speed_increment;
    ball->velocity_x = speed * cosf(angle);
    ball->velocity_y = speed * sinf(angle);
    
    // Reset last hit
    ball->last_hit_by = 0;
}

// Draw the ball on the screen
void draw_ball(SDL_Renderer* renderer, Ball ball) {
    // Set ball color
    SDL_SetRenderDrawColor(renderer, BALL_R, BALL_G, BALL_B, BALL_A);
    
    // Draw ball
    SDL_RenderFillRect(renderer, &ball.rect);
}
