#pragma once
#include "balloon.h"
#include "balloon_list.h"
#include "entity_list.h"
#include "input.h"
#include "map.h"
#include "player.h"

#define GRAVITY_VELOCITY 1000
#define BALLOON_COUNT 3

typedef struct {
    Map map;
    Player player;
    Entity_list entities;
    Balloon_list balloons;
} Game;

int game_init(Game* g);
int game_loop(Game* g, Input i, float dt);
void game_destroy(Game* g);