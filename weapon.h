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