#pragma once
#include "balloon.h"
#include <errno.h>
#include <raylib.h>
#include <raymath.h>

int balloon_init(Balloon* b) {
    b->position = (Vector2){ .x = 220.0f, .y = 150.0f };
    b->velocity = (Vector2){ .x = BALLOON_HORIZOTNAL_SPEED, .y = 0.0f };

    b->texture = LoadTexture(BALLOON_TEXTURE_PATH);
    if (!IsTextureValid(b->texture)) {
        return EIO;
    }

    b->dimensions = (Vector2){ .x = b->texture.width, .y = b->texture.height };

    return 0;
}

void balloon_update_velocity(Balloon* b, float gravity_velocity) {
    //b->velocity.y += gravity_velocity;
}

void balloon_update_movement(Balloon* b, float dt) {
    b->position.x += b->velocity.x * dt;
    b->position.y += b->velocity.y * dt;
}

void balloon_draw(Balloon* b) {
    DrawTexture(b->texture, b->position.x, b->position.y, WHITE);
}

void balloon_destroy(Balloon* b) {
    if (IsTextureValid(b->texture)) {
        UnloadTexture(b->texture);
    }
}
