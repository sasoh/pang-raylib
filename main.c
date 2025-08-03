#include "map.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TARGET_FPS 100

int main() {
    Map* current_map = NULL;

    Vector2 endPoint = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pang!");
    SetTargetFPS(TARGET_FPS);
    while(!WindowShouldClose()) {
        if (!current_map) {
            current_map = map_load();
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    map_destroy(current_map);
    return 0;
}