#include <stdio.h>
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TARGET_FPS 100

void game_loop() {
    Vector2 endPoint = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window test");
    SetTargetFPS(TARGET_FPS);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}