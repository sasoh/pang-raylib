#pragma once
#include "map.h"
#include "player.h"

typedef struct {
    Map map;
    Player player;
} Game;

int game_init(Game* g);
int game_loop(Game* g);
void game_destroy(Game* g);