#pragma once
#include <raylib.h>

typedef struct {
    int* tiles;
    int rows;
    int columns;
    int tile_size;
    Texture2D textures[2];
} Map;

int map_init(Map* m);
bool map_is_colliding_horizontal(Map* m, Vector2 position, float size);
void map_draw(Map* m);
void map_destroy(Map* m);