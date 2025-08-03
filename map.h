#ifndef MAP_H
#define MAP_H

#include <raylib.h>

typedef struct {
    int* tiles;
    int rows;
    int columns;
    Texture2D textures[2];
} Map;

Map *map_load(void);
void map_destroy(Map *m);

#endif