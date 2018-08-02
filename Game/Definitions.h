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

// Input
#define JUMP_KEY S
#define COLLECT_KEY A
#define ESCAPE_KEY Escape
#define ENTER_KEY Return
#define JUMP_BUTTON 1
#define COLLECT_BUTTON 2
#define PAUSE_BUTTON 9
#define RESTART_BUTTON 8
#define QUIT_BUTTON 9
#define STICK_SENSITIVITY 10

// Player
#define PLAYER_WIDTH 192
#define PLAYER_HEIGHT 288
#define PLAYER_LIVES 3
#define PLAYER_MOVE_SPEED 500
#define PLAYER_JUMP_SPEED -1000
#define PLAYER_JUMP_HEIGHT 576
#define GRAVITY 1200
#define GROUND_HEIGHT 72
#define FLICKERING_TIME 5
#define FLICKERING_RATE 0.5
#define IDLE_MAX_INDEX 5
#define MOVING_MAX_INDEX 5
#define JUMPING_MAX_INDEX 2
#define IDLE_FRAME_TIME 1.0f / 6.0f
#define MOVING_FRAME_TIME 1.0f / 12.0f
#define JUMPING_FRAME_TIME 1.0f / 18.0f 

// Fruits
#define FRUITS 5
#define FRUIT_WIDTH 64
#define FRUIT_HEIGHT 45
#define FRUIT_MIN_SPEED 2
#define FRUIT_MAX_SPEED 30
#define FRUIT_MIN_X 45
#define FRUIT_MAX_X 1555
#define FRUIT_MIN_Y 90
#define FRUIT_MIN_SPAWN_TIME 3
#define FRUIT_MAX_SPAWN_TIME 15
#define WATERMELON_SCORE 1
#define APPLE_SCORE 2
#define PEAR_SCORE 3
#define BANANA_SCORE 4
#define FRUIT_MAX_INDEX 3

// Collectibles
#define COLLECTIBLE_MIN_X 32
#define COLLECTIBLE_MAX_X 1578
#define COLLECTIBLE_MIN_Y 400
#define COLLECTIBLE_MAX_Y 738
#define COLLECTIBLE_START_FLICKERING 2.5

#define COINS 3
#define COIN_DURATION 7.5f
#define COIN_SCORE 5
#define COIN_WIDTH 64
#define COIN_HEIGHT 90
#define COIN_MIN_SPAWN_TIME 3
#define COIN_MAX_SPAWN_TIME 20
#define COIN_MAX_INDEX 2
#define COIN_FRAME_TIME 1.0f / 6.0f

#define LIFE_DURATION 5
#define LIFE_WIDTH 96
#define LIFE_HEIGHT 90
#define LIFE_MIN_SPAWN_TIME 10
#define LIFE_MAX_SPAWN_TIME 60
#define LIFE_MAX_INDEX 1
#define LIFE_FRAME_TIME 1.0f / 3.0f 

#define GAME_TIME 120
#define TIME_BONUS_TIME 20
#define TIME_BONUS_DURATION 5
#define TIME_BONUS_WIDTH 96
#define TIME_BONUS_HEIGHT 90
#define TIME_BONUS_MIN_SPAWN_TIME 20
#define TIME_BONUS_MAX_SPAWN_TIME 40
#define TIME_BONUS_MAX_INDEX 1
#define TIME_BONUS_FRAME_TIME 1.0f / 3.0f 

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
#define WINDOW_ICON_PATH "Assets/Images/Icon.png"
#define SPLASH_LOGO_PATH "Assets/Images/Splash Logo.png"
#define PLAYER_PATH "Assets/Images/Player.png"
#define FRUIT_PATH "Assets/Images/Fruit.png"
#define COIN_PATH "Assets/Images/Coin.png"
#define LIFE_PATH "Assets/Images/Life.png"
#define TIME_BONUS_PATH "Assets/Images/Time Bonus.png"
#define GROUND_PATH "Assets/Images/Ground.png"
#define SKY_PATH "Assets/Images/Sky Backdrop.png"

// Sounds File Paths
#define MAIN_THEME "Assets/Sounds/Music.wav"
#define JUMP_SOUND "Assets/Sounds/Jump.wav"
#define FRUIT_HIT_SOUND "Assets/Sounds/Fruit Hit.wav"
#define FRUIT_CRASH_SOUND "Assets/Sounds/Fruit Crash.wav"
#define GAME_OVER_SOUND "Assets/Sounds/Game Over.wav"
#define PICK_UP_COIN_SOUND "Assets/Sounds/Pick Up Coin.wav"
#define PICK_UP_LIFE_SOUND "Assets/Sounds/Pick Up Life.wav"
#define PICK_UP_TIME_BONUS_SOUND "Assets/Sounds/Pick Up Time Bonus.wav"
#define CLOCK_TICK_SOUND "Assets/Sounds/Clock Tick.wav"
#define SELECT_SOUND "Assets/Sounds/Select.wav"

// Fonts File Paths
#define FONT_PATH "Assets/Fonts/Last Ninja.ttf"

#endif