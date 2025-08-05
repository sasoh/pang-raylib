#include "game.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 840
#define TARGET_FPS 60
#define BACKGROUND_COLOR CLITERAL(Color){ 210, 230, 255, 255 }

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pang!");
    SetTargetFPS(TARGET_FPS);

    int init = game_init();
    if (init == ENODATA) {
        printf("Failed to init game, quitting.\n");
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        int loop_status = game_loop();
        if (loop_status != 0) {
            break;
        }

        EndDrawing();
    }
    CloseWindow();

    game_destroy();

    return EXIT_SUCCESS;
}