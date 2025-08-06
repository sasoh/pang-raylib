#pragma once
#include <raylib.h>

typedef struct {
    int* tiles;
    int rows;
    int columns;
    Texture2D textures[2];
} Map;

int map_init(Map* m);
void map_draw(Map* m);
void map_destroy(Map* m);