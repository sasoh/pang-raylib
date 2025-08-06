#pragma once
#include <stdbool.h>

typedef struct {
    bool isLeftPressed;
    bool isRightPressed;
} Input;

Input input_state(void);