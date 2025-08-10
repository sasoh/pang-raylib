#pragma once
#include "input.h"
#include "weapon.h"
#include <raylib.h>

#define PLAYER_TEXTURE_PATH "assets/player-idle-01.png"
#define PLAYER_HORIZOTNAL_SPEED 550

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    Vector2 dimensions;
    Weapon weapon;
} Player;

int player_init(Player* p);
void player_update_input(Player* p, Input i);
void player_update_velocity(Player* p, float gravity_velocity);
void player_update_movement(Player* p, float dt);
void player_draw(Player* p);
void player_destroy(Player* p);
void player_horizontal_collision_points(Player* p, Vector2** points, int* points_count, float dt);
void player_vertical_collision_points(Player* p, Vector2** points, int* points_count, float dt);
void player_collision_points_destroy(Vector2* points);