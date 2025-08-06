#include "input.h"
#include <raylib.h>

Input input_state(void) {
    return (Input) { .isLeftPressed = IsKeyDown(KEY_LEFT), .isRightPressed = IsKeyDown(KEY_RIGHT) };
}