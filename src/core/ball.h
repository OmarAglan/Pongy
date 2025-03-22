#ifndef BALL_H
#define BALL_H

#include <SDL3/SDL.h>
#include <stdbool.h>
#include "paddle.h"

// Ball structure
typedef struct {
    SDL_FRect rect;        // Position and size
    float velocity_x;      // Horizontal velocity
    float velocity_y;      // Vertical velocity
    float base_speed;      // Base speed factor
    float speed_increment; // Speed increases over time
    int last_hit_by;       // Which player last hit the ball (1 or 2)
} Ball;

// Initialize the ball
void init_ball(Ball* ball);

// Update ball position and handle collisions
// Returns: 1 if player 1 scores, 2 if player 2 scores, 0 otherwise
int update_ball(Ball* ball, Paddle* player1, Paddle* player2);

// Reset the ball to the center after scoring
void reset_ball(Ball* ball, int scored_by);

// Draw the ball on the screen
void draw_ball(SDL_Renderer* renderer, Ball ball);

// Check if the ball collides with a paddle
bool check_paddle_collision(Ball* ball, Paddle* paddle, int paddle_id);

#endif // BALL_H
