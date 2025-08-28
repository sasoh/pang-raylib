#pragma once
#include "entity.h"
#include <raylib.h>

#define PROJECTILE_TEXTURE_PATH "assets/weapon-01.png"
#define PROJECTILE_SPEED 450

typedef struct {
    Entity entity;
    bool is_shot;
} Weapon;

int weapon_init(Weapon* w);
void weapon_shoot(Weapon* w, Vector2 position);
Vector2 weapon_collision_point(Weapon* w, float dt);
void weapon_stop(Weapon* w);
void weapon_destroy(Weapon* w);