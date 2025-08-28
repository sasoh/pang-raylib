#pragma once
#include "entity.h"
#include <raylib.h>

typedef struct {
    Entity* entities;
    int* tiles;
    int rows;
    int columns;
    int tile_size;
} Map;

int map_init(Map* m);
bool map_check_collision(Map* m, Vector2 position);
bool map_check_within_boundaries(Map* m, Vector2 position);
void map_destroy(Map* m);