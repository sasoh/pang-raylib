#pragma once
#include "balloon.h"
#include "input.h"
#include "map.h"
#include "player.h"

#define GRAVITY_VELOCITY 30

typedef struct {
    Map map;
    Player player;
    Balloon balloon[3];
    int balloon_count;
} Game;

int game_init(Game* g);
int game_loop(Game* g, Input i, float dt);
void game_destroy(Game* g);