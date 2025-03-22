#ifndef CONFIG_H
#define CONFIG_H

// Window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Paddle dimensions
#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 70
#define PADDLE_SPEED 7.0f
#define PADDLE_ACCELERATION 0.8f
#define PADDLE_DECELERATION 0.9f
#define PADDLE_MAX_SPEED 12.0f

// Ball settings
#define BALL_SIZE 15
#define BALL_INITIAL_SPEED 5.0f
#define BALL_SPEEDUP_FACTOR 0.2f
#define BALL_MAX_SPEEDUP 10.0f
#define BALL_MAX_BOUNCE_ANGLE 1.0f
#define BALL_PADDLE_INFLUENCE 0.3f
#define BALL_SPEEDUP_RETENTION 0.7f

// Menu settings
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_PADDING 20
#define TITLE_PADDING 80

// Colors
#define BACKGROUND_R 0
#define BACKGROUND_G 0
#define BACKGROUND_B 40
#define BACKGROUND_A 255

#define PADDLE_R 220
#define PADDLE_G 220
#define PADDLE_B 255
#define PADDLE_A 255

#define BALL_R 255
#define BALL_G 255
#define BALL_B 255
#define BALL_A 255

#define LINE_R 100
#define LINE_G 100
#define LINE_B 150
#define LINE_A 255

#define BUTTON_NORMAL_R 60
#define BUTTON_NORMAL_G 60
#define BUTTON_NORMAL_B 120
#define BUTTON_NORMAL_A 255

#define BUTTON_HOVER_R 80
#define BUTTON_HOVER_G 80
#define BUTTON_HOVER_B 160
#define BUTTON_HOVER_A 255

#define BUTTON_TEXT_R 230
#define BUTTON_TEXT_G 230
#define BUTTON_TEXT_B 255
#define BUTTON_TEXT_A 255

#define TITLE_R 220
#define TITLE_G 220
#define TITLE_B 255
#define TITLE_A 255

#endif // CONFIG_H