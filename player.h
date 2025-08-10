#pragma once
#include "input.h"
#include "entity.h"
#include "weapon.h"
#include <raylib.h>

#define PLAYER_TEXTURE_PATH "assets/player-idle-01.png"
#define PLAYER_HORIZOTNAL_SPEED 550

typedef struct {
    Entity entity;
    Weapon weapon;
} Player;

int player_init(Player* p);
void player_update_input(Player* p, Input i);
void player_horizontal_collision_points(Player* p, Vector2** points, int* points_count, float dt);
void player_vertical_collision_points(Player* p, Vector2** points, int* points_count, float dt);
void player_collision_points_destroy(Vector2* points);