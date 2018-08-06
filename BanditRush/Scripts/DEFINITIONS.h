#pragma once

// --- System ---
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define MAX_FRAMERATE 60

#define SPLASH_SCREEN_TIME 2.5f

#define LEVEL_01 734.0f
#define LEVEL_02 429.0f
#define LEVEL_03 239.0f

// --- Player ---
#define PLAYER_SCALE 1.35f
#define CHARACTER_WIDTH 24.0f
#define CHARACTER_HEIGHT 40.0f

// horizontal movement
#define STATIONARY 0.0f
#define RUN_SPEED 200.0f
#define STUMBLE_SPEED 35.0f
#define FALL_DRIFT 200.0f
#define FLIP_SPEED 370.0f
#define DASH_SPEED 600.0f
#define DASH_CD 1.0f

// vertical movement
#define JUMP_FORCE 600.0f
#define FLIP_DELAY 0.75f
#define GRAVITY 20.0f

// attacking
#define ATTACK1_SPEED 11.0f
#define ATTACK2_SPEED 13.0f
#define ATTACK3_SPEED 9.0f
#define ATTACK_RANGE 50.0f
#define ATTACK_DAMAGE 100.0f


// --- Enemy ---
#define MAX_ENEMIES 30
#define ENEMY_SCALE 1.4f
#define ENEMY_CENTER 0.725f

#define ENEMY_WIDTH 24.0f
#define ENEMY_HEIGHT 28.0f

#define ENEMY_HEALTH 175.0f

// position & movement
#define ENEMY_RUN_SPEED 80.0f

// attacking
#define ENEMY_ATTACK_DAMAGE 100.0f
#define ENEMY_ATTACK_RANGE 30.0f
#define ENEMY_HIT_RANGE 35.0f
#define ENEMY_ATTACK_CD 3.0f


// --- Other ---
#define DMG_TXT_MOVE_SPEED 50.0f
#define DMG_TXT_FADE_SPEED 3

