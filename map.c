#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAP_ROW_MAX_WIDTH 100

typedef struct {
    int* tiles;
    int rows;
    int columns;
} Map;

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

void map_destroy(Map* m) {
    if (m == NULL) return;
    if (m->tiles != NULL) {
        free(m->tiles);
    }
    free(m);
}

void map_print(Map* m) {
    if (m == NULL || m->tiles == NULL) return;
    printf("Map size: %dx%d\n", m->columns, m->rows);
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->columns; j++) {
            printf("%d ", m->tiles[i * m->columns + j]);
        }
        printf("\n");
    }
}

int char_to_int(char c) {
    return (int)(c - '0');
}

void load_map_from_file(void) {
    FILE* map_csv = fopen("map-loader-level-1.csv", "r");
    if (map_csv != NULL) {

        // Count columns & rows.
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

        Map* m = map_create(rows, columns);
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

        map_print(m);

        map_destroy(m);
        fclose(map_csv);
    }
    else {
        printf("Failed to open map for parsing.\n");
    }
}