#pragma once
#include "input.h"
#include "map.h"
#include "player.h"

#define GRAVITY_VELOCITY 30

typedef struct {
    Map map;
    Player player;
} Game;

int game_init(Game* g);
int game_loop(Game* g, Input i, float dt);
void game_destroy(Game* g);