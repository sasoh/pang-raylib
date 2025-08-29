#pragma once
#include "balloon.h"
#include "entity_list.h"
#include "input.h"
#include "map.h"
#include "player.h"

#define GRAVITY_VELOCITY 1000
#define BALLOON_COUNT 3

typedef struct {
    Map map;
    Player player;
    Balloon balloon[BALLOON_COUNT];
    Entity_list entities;
} Game;

int game_init(Game* g);
int game_loop(Game* g, Input i, float dt);
void game_destroy(Game* g);