#pragma once
#include "input.h"
#include <raylib.h>

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
} Player;

int player_init(Player* p);
void player_update_input(Player* p, Input i);
void player_update_movement(Player* p, float dt);
void player_draw(Player* p);
void player_destroy(Player* p);