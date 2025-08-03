#include "map.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEVEL_PATH "assets/map-loader-level-1.csv"
#define TILE01_PATH "assets/tile-01.png"
#define TILE02_PATH "assets/tile-02.png"
#define TILE_PIXEL_SIZE 70
#define MAP_ROW_MAX_WIDTH 100

Map* map_create(int rows, int columns) {
    Map* m = (Map*)malloc(sizeof(Map));
    if (m == NULL) {
        printf("Failed to allocate map.\n");
        return NULL;
    }
    m->rows = rows;
    m->columns = columns;
    m->tiles = malloc(rows * columns * sizeof(int));

    return m;
}

Texture2D map_texture(Map* m, int index) {
    Texture2D result = { 0 };

    if (index == 2) {
        result = m->textures[0];
    }
    else if (index == 3) {
        result = m->textures[1];
    }

    return result;
}

void map_draw(Map* m) {
    for (size_t y = 0; y < m->rows; y++) {
        for (size_t x = 0; x < m->columns; x++) {
            int current_tile = map_tile(m, x, y);
            Texture2D tile_texture = map_texture(m, current_tile);
            if (IsTextureValid(tile_texture)) {
                DrawTexture(
                    tile_texture,
                    x * TILE_PIXEL_SIZE,
                    y * TILE_PIXEL_SIZE,
                    WHITE
                );
            }
        }
    }
}

int map_tile(Map* m, int x, int y) {
    return m->tiles[x + y * m->columns];
}

void map_destroy(Map* m) {
    if (m == NULL) return;
    if (m->tiles != NULL) {
        free(m->tiles);
    }
    UnloadTexture(m->textures[0]);
    UnloadTexture(m->textures[1]);
    free(m);
}

void map_print(Map* m) {
    if (m == NULL || m->tiles == NULL) return;
    printf("Map size: %dx%d\n", m->columns, m->rows);
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->columns; j++) {
            printf("%d ", map_tile(m, j, i));
        }
        printf("\n");
    }
}

int char_to_int(char c) {
    return (int)(c - '0');
}

Map* map_load(void) {
    Map* m = NULL;
    FILE* map_csv = fopen(LEVEL_PATH, "r");
    if (map_csv != NULL) {
        char line_buffer[MAP_ROW_MAX_WIDTH];
        int line_counter = 0;
        size_t rows = 0;
        size_t columns = 0;
        while (fgets(line_buffer, MAP_ROW_MAX_WIDTH, map_csv) != 0) {
            line_counter++;
            if (columns == 0) {
                for (size_t i = 0; i < strlen(line_buffer); i++) {
                    if (isdigit(line_buffer[i])) {
                        columns++;
                    }
                }
            }
        }
        rows = line_counter;

        m = map_create(rows, columns);
        rewind(map_csv);
        for (size_t i = 0; i < m->rows; i++) {
            fgets(line_buffer, MAP_ROW_MAX_WIDTH, map_csv);
            size_t column_counter = 0;
            for (size_t j = 0; j < strlen(line_buffer); j++) {
                char c = line_buffer[j];
                if (isdigit(c)) {
                    m->tiles[i * m->columns + column_counter] = char_to_int(c);
                    column_counter++;
                }
            }
        }
        fclose(map_csv);

        m->textures[0] = LoadTexture(TILE01_PATH);
        m->textures[1] = LoadTexture(TILE02_PATH);

        map_print(m);
    }
    else {
        printf("Failed to open %s for parsing.\n", LEVEL_PATH);
    }

    return m;
}