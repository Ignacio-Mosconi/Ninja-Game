#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Game Properties
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define FRAME_RATE 60

// Splash State
#define SPLASH_STATE_DURATION 2.5

// Menu State
#define MENU_OPTIONS 2
#define TITLE_TEXT_SIZE 160
#define OPTIONS_TEXT_SIZE 80

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
#define COLLECTIBLE_MIN_X 32
#define COLLECTIBLE_MAX_X 1578
#define COLLECTIBLE_MIN_Y 400
#define COLLECTIBLE_MAX_Y 738

#define COINS 3
#define COIN_DURATION 5
#define COIN_SCORE 5
#define COIN_WIDTH 64
#define COIN_HEIGHT 90
#define COIN_MIN_SPAWN_TIME 3
#define COIN_MAX_SPAWN_TIME 20

#define LIFE_DURATION 5
#define LIFE_WIDTH 64
#define LIFE_HEIGHT 90
#define LIFE_MIN_SPAWN_TIME 10
#define LIFE_MAX_SPAWN_TIME 60

// Heads Up Display
#define HUD_TEXT_Y 15
#define HUD_TEXT_SIZE 60
#define PAUSED_TEXT_SIZE 90
#define GAME_OVER_TEXT_SIZE 120
#define HUD_OPTIONS_TEXT_SIZE 32
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
#define LIFE_PATH "Assets/Images/Life.png"

// Sounds File Paths
#define MAIN_THEME "Assets/Sounds/Music.wav"
#define JUMP_SOUND "Assets/Sounds/Jump.wav"
#define FRUIT_HIT_SOUND "Assets/Sounds/Fruit Hit.wav"
#define PICK_UP_COIN_SOUND "Assets/Sounds/Pick Up Coin.wav"
#define PICK_UP_LIFE_SOUND "Assets/Sounds/Pick Up Life.wav"
#define SELECT_SOUND "Assets/Sounds/Select.wav"

// Fonts File Paths
#define FONT_PATH "Assets/Fonts/Last Ninja.ttf"


#endif