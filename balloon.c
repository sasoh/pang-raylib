#pragma once
#include "balloon.h"
#include <errno.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

int balloon_init(Balloon* b, Vector2 position, bool intial_direction_right, float max_velocity) {
    b->position = position;
    int direction_multiplier = intial_direction_right ? 1 : -1;
    b->velocity = (Vector2){ .x = direction_multiplier * BALLOON_HORIZOTNAL_SPEED, .y = 0.0f };

    b->texture = LoadTexture(BALLOON_TEXTURE_PATH);
    if (!IsTextureValid(b->texture)) {
        return EIO;
    }

    b->dimensions = (Vector2){ .x = b->texture.width, .y = b->texture.height };
    b->max_velocity = max_velocity;

    return 0;
}

void balloon_update_velocity(Balloon* b, float gravity_velocity) {
    b->velocity.y += gravity_velocity;
}

void balloon_update_movement(Balloon* b, float dt) {
    b->position.x += b->velocity.x * dt;
    b->position.y += b->velocity.y * dt;
}

void balloon_horizontal_collision_points(Balloon* b, Vector2** points, int* points_count, float dt) {
    // two points - middle left and middle right
    *points = (Vector2*)malloc(2 * sizeof(Vector2));
    if (*points == NULL) {
        *points_count = 0;
        return;
    }
    *points_count = 2;

    (*points)[0] = (Vector2){
        .x = b->position.x + b->velocity.x * dt,
        .y = b->position.y + b->dimensions.y / 2
    };
    (*points)[1] = (Vector2){
        .x = b->position.x + b->velocity.x * dt + b->dimensions.x,
        .y = b->position.y + b->dimensions.y / 2
    };
}

void balloon_vertical_collision_points(Balloon* b, Vector2** points, int* points_count, float dt) {
    // two points - top center and bottom center
    *points = (Vector2*)malloc(2 * sizeof(Vector2));
    if (*points == NULL) {
        *points_count = 0;
        return;
    }
    *points_count = 2;

    (*points)[0] = (Vector2){
        .x = b->position.x + b->dimensions.x / 2,
        .y = b->position.y + b->velocity.y * dt
    };
    (*points)[1] = (Vector2){
        .x = b->position.x + b->dimensions.x / 2,
        .y = b->position.y + b->velocity.y * dt + b->dimensions.y
    };
}

void balloon_collision_points_destroy(Vector2* points) {
    free(points);
}

void balloon_horizontal_collision(Balloon* b) {
    b->velocity.x *= -1;
}

void balloon_vertical_collision(Balloon* b) {
    b->velocity.y *= -1;
    b->velocity.y = Clamp(b->velocity.y, -b->max_velocity, b->max_velocity);
}

void balloon_draw(Balloon* b) {
    DrawTexture(b->texture, b->position.x, b->position.y, WHITE);
}

void balloon_destroy(Balloon* b) {
    if (IsTextureValid(b->texture)) {
        UnloadTexture(b->texture);
    }
}
