#pragma once
#include <stdbool.h>

typedef struct {
    bool is_left_pressed;
    bool is_right_pressed;
    bool is_shoot_pressed;
} Input;

Input input_state(void);