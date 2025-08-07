#pragma once
#include "input.h"
#include <raylib.h>

#define PLAYER_TEXTURE_PATH "assets/player-idle-01.png"
#define PLAYER_HORIZOTNAL_SPEED 550

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    Vector2 dimensions;
} Player;

int player_init(Player* p);
void player_update_input(Player* p, Input i, float gravity_velocity);
void player_update_movement(Player* p, float dt);
void player_draw(Player* p);
void player_destroy(Player* p);