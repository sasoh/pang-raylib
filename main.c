#include "game.h"
#include <errno.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 840
#define TARGET_FPS 100
#define BACKGROUND_COLOR CLITERAL(Color){ 210, 230, 255, 255 }

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pang!");
    SetTargetFPS(TARGET_FPS);

    Game g;
    int init_status = game_init(&g);
    if (init_status == ENODATA || init_status == ENOMEM) {
        printf("Failed to load game resources, quitting.\n");
        return EXIT_FAILURE;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        int loop_status = game_loop(&g, input_state(), GetFrameTime());
        if (loop_status != 0) {
            break;
        }

        EndDrawing();
    }
    CloseWindow();

    game_destroy(&g);

    return EXIT_SUCCESS;
}