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
    m->entities = malloc(rows * columns * sizeof(Entity));
}

static int map_index(int x, int y, int columns) {
    return x + y * columns;
}

void map_destroy(Map* m) {
    if (m->tiles != NULL) {
        free(m->tiles);
    }
    if (m->entities != NULL) {
        for (int i = 0; i < m->rows * m->columns; i++) {
            entity_destroy(&m->entities[i]);
        }
        free(m->entities);
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
                    // create entity here
                    int c_uint = c - '0';

                    char* tile_texture_path = NULL;
                    if (c_uint == 2) {
                        tile_texture_path = TILE01_PATH;
                    }
                    else if (c_uint == 3) {
                        tile_texture_path = TILE02_PATH;
                    }
                    Entity *e = &m->entities[map_index(x, y, m->columns)];
                    entity_init(
                        e,
                        Layer_Level,
                        false,
                        tile_texture_path != NULL,
                        tile_texture_path
                    );
                    e->position = (Vector2){ .x = x * e->dimensions.x, .y = y * e->dimensions.y };
                    m->tile_size = e->dimensions.x;
                    m->tiles[map_index(x, y, m->columns)] = c_uint;
                    x++;
                }
            }
        }
        fclose(map_csv);
        
        map_print(m);
    }
    else {
        return EIO;
    }

    return 0;
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

bool map_check_within_boundaries(Map* m, Vector2 position)
{
    int map_width = m->columns * m->tile_size;
    int map_height = m->rows* m->tile_size;
    return position.x > 0 && position.x < map_width && position.y > 0 && position.y < map_height;
}
