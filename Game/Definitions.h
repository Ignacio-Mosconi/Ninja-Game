#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Game Properties
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

// Splash State
#define SPLASH_STATE_DURATION 0.5

// Player
#define PLAYER_WIDTH 256
#define PLAYER_HEIGHT 288
#define PLAYER_LIVES 3
#define PLAYER_MOVE_SPEED 500
#define PLAYER_JUMP_SPEED -1000
#define PLAYER_JUMP_HEIGHT 576
#define GRAVITY 1200
#define GROUND_HEIGHT 72

// Fruits
#define FRUITS 5
#define FRUIT_WIDTH 64
#define FRUIT_HEIGHT 45
#define FRUIT_MIN_SPEED 2
#define FRUIT_MAX_SPEED 30
#define FRUIT_MIN_X 32
#define FRUIT_MAX_X 1578
#define FRUIT_MIN_Y 90
#define FRUIT_MIN_SPAWN_TIME 3
#define FRUIT_MAX_SPAWN_TIME 12

// Collectibles
#define COINS 2
#define COIN_DURATION 5
#define COIN_WIDTH 64
#define COIN_HEIGHT 90
#define COIN_MIN_SPAWN_TIME 5
#define COIN_MAX_SPAWN_TIME 30
#define COIN_MIN_X 32
#define COIN_MAX_X 1578
#define COIN_MIN_Y 400
#define COIN_MAX_Y 738

// Heads Up Display
#define HUD_TEXT_Y 15
#define HUD_TEXT_SIZE 60
#define PAUSED_TEXT_SIZE 90
#define GAME_OVER_TEXT_SIZE 120
#define TEXT_COLOR_RED {128, 32, 32, 255}
#define TEXT_COLOR_GREEN {32, 128, 32, 255}
#define TEXT_COLOR_BLUE {32, 32, 128, 255}
#define TEXT_COLOR_YELLOW {200, 128, 32, 255}

// Images File Paths
#define SPLASH_LOGO_PATH "Assets/Images/Splash Logo.png"
#define PLAYER_PATH "Assets/Images/Player.png"
#define FRUIT_PATH "Assets/Images/Fruit.png"
#define GROUND_PATH "Assets/Images/Ground.png"
#define COIN_PATH "Assets/Images/Coin.png"

// Fonts File Paths
#define FONT_PATH "Assets/Fonts/Last Ninja.ttf"

#endif
