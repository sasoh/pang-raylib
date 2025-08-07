#include "map.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LEVEL_PATH "assets/map-loader-level-1.csv"
#define TILE01_PATH "assets/tile-01.png"
#define TILE02_PATH "assets/tile-02.png"
#define MAP_ROW_MAX_WIDTH 100

#define TILE_BLANK 1

static void map_create(Map* m, int rows, int columns) {
    m->rows = rows;
    m->columns = columns;
    m->tiles = malloc(rows * columns * sizeof(int));
}

static Texture2D map_texture(Map* m, int index) {
    Texture2D result = { 0 };

    if (index == 2) {
        result = m->textures[0];
    }
    else if (index == 3) {
        result = m->textures[1];
    }

    return result;
}

static int map_index(int x, int y, int columns) {
    return x + y * columns;
}

void map_draw(Map* m) {
    for (int y = 0; y < m->rows; y++) {
        for (int x = 0; x < m->columns; x++) {
            int current_tile = m->tiles[map_index(x, y, m->columns)];
            Texture2D tile_texture = map_texture(m, current_tile);
            if (IsTextureValid(tile_texture)) {
                DrawTexture(
                    tile_texture,
                    x * tile_texture.width,
                    y * tile_texture.height,
                    WHITE
                );
            }
        }
    }
}

void map_destroy(Map* m) {
    if (m->tiles != NULL) {
        free(m->tiles);
    }
    if (IsTextureValid(m->textures[0])) {
        UnloadTexture(m->textures[0]);
    }
    if (IsTextureValid(m->textures[1])) {
        UnloadTexture(m->textures[1]);
    }
}

static void map_print(Map* m) {
    if (m == NULL || m->tiles == NULL) return;
    printf("Map size: %dx%d\n", m->columns, m->rows);
    for (int y = 0; y < m->rows; y++) {
        for (int x = 0; x < m->columns; x++) {
            printf("%d ", m->tiles[map_index(x, y, m->columns)]);
        }
        printf("\n");
    }
}

int map_init(Map* m) {
    FILE* map_csv = fopen(LEVEL_PATH, "r");
    if (map_csv != NULL) {
        char line_buffer[MAP_ROW_MAX_WIDTH];
        int line_counter = 0;
        int rows = 0;
        int columns = 0;
        while (fgets(line_buffer, MAP_ROW_MAX_WIDTH, map_csv) != 0) {
            line_counter++;
            if (columns == 0) {
                for (int i = 0; i < strlen(line_buffer); i++) {
                    if (isdigit(line_buffer[i])) {
                        columns++;
                    }
                }
            }
        }
        rows = line_counter;

        map_create(m, rows, columns);
        rewind(map_csv);
        for (int y = 0; y < m->rows; y++) {
            fgets(line_buffer, MAP_ROW_MAX_WIDTH, map_csv);
            int x = 0;
            for (int j = 0; j < strlen(line_buffer); j++) {
                char c = line_buffer[j];
                if (isdigit(c)) {
                    m->tiles[map_index(x, y, m->columns)] = atoi(&c);
                    x++;
                }
            }
        }
        fclose(map_csv);

        m->textures[0] = LoadTexture(TILE01_PATH);
        m->textures[1] = LoadTexture(TILE02_PATH);

        m->tile_size = m->textures[0].width;

        map_print(m);
    }
    else {
        return EIO;
    }

    return 0;
}

bool map_is_colliding_horizontal(Map* m, Vector2 position, Vector2 dimensions) {
    int index_left = map_index(
        floor((position.x / (m->columns * m->tile_size)) * m->columns),
        floor(((position.y + dimensions.y / 2) / (m->rows * m->tile_size)) * m->rows),
        m->columns
    );
    int index_right = map_index(
        floor(((position.x + dimensions.x) / (m->columns * m->tile_size)) * m->columns),
        floor(((position.y + dimensions.y / 2) / (m->rows * m->tile_size)) * m->rows),
        m->columns
    );
    int tile_left = m->tiles[index_left];
    int tile_right = m->tiles[index_right];

    return tile_left != TILE_BLANK || tile_right != TILE_BLANK;
}

bool map_is_colliding_vertical(Map* m, Vector2 position, Vector2 dimensions) {
    int index_below = map_index(
        floor(((position.x + dimensions.x / 2) / (m->columns * m->tile_size)) * m->columns),
        floor(((position.y + dimensions.y) / (m->rows * m->tile_size)) * m->rows),
        m->columns
    );
    int tile_below = m->tiles[index_below];

    return tile_below != TILE_BLANK;
}

bool map_check_collision(Map* m, Vector2 position) {
    int x = floorf((position.x / (m->columns * m->tile_size)) * m->columns);
    int y = floorf((position.y / (m->rows * m->tile_size)) * m->rows);
    int index = map_index(x, y, m->columns);
    if (index >= m->columns * m->rows) {
        printf("Queried %.1fx%.1f coordinate [%d, %d] index %d outside of map\n", position.x, position.y, x, y, index);
        return true;
    }
    int tile = m->tiles[index];
    
    return tile != TILE_BLANK;
}
