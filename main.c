#include "map.h"
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 840
#define TARGET_FPS 100
#define BACKGROUND_COLOR CLITERAL(Color){ 210, 230, 255, 255 }

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pang!");
    SetTargetFPS(TARGET_FPS);

    Map* current_map = map_load();
    if (current_map == NULL) {
        printf("Failed to load map, quitting.\n");
        return EXIT_FAILURE;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        map_draw(current_map);
        EndDrawing();
    }
    CloseWindow();
    map_destroy(current_map);

    return EXIT_SUCCESS;
}