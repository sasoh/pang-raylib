#pragma once
#include <raylib.h>

#define PROJECTILE_TEXTURE_PATH "assets/weapon-01.png"
#define PROJECTILE_SPEED 450

// TODO: Weapon, Player and Balloon types share a lot of commonality, extract/abstract it.
typedef struct {
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    Vector2 dimensions;
    bool is_shot;
} Weapon;

int weapon_init(Weapon* w);
void weapon_shoot(Weapon* w, Vector2 position);
void weapon_update_movement(Weapon* w, float dt);
void weapon_draw(Weapon* w);
void weapon_destroy(Weapon* w);