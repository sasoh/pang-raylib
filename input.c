#include "input.h"
#include <raylib.h>

Input input_state(void) {
    return (Input) {
        .is_left_pressed = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A),
        .is_right_pressed = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D),
        .is_shoot_pressed = IsKeyDown(KEY_SPACE)
    };
}