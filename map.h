#pragma once
#include <raylib.h>

typedef struct {
    int* tiles;
    int rows;
    int columns;
    Texture2D textures[2];
} Map;

Map* map_load(void);
void map_draw(Map* m);
void map_destroy(Map* m);
int map_tile(Map* m, int x, int y);