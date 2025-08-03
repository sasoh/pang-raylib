#include "map.h"
#include <stdio.h>

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 840
#define TARGET_FPS 100

int main() {
    Map* current_map = NULL;
    Color background_color = {
        .r = 210,
        .g = 230,
        .b = 255,
        .a = 255
    };

    Vector2 endPoint = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pang!");
    SetTargetFPS(TARGET_FPS);
    while(!WindowShouldClose()) {
        if (!current_map) {
            current_map = map_load();
        }
        BeginDrawing();
        ClearBackground(background_color);
        map_draw(current_map);
        EndDrawing();
    }
    CloseWindow();
    map_destroy(current_map);
    return 0;
}