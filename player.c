#include "player.h"
#include <errno.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

int player_init(Player* p) {
    p->position = (Vector2){ .x = 120, .y = 650 };
    p->velocity = Vector2Zero();

    p->texture = LoadTexture(PLAYER_TEXTURE_PATH);
    if (!IsTextureValid(p->texture)) {
        return EIO;
    }

    p->dimensions = (Vector2){ .x = p->texture.width, .y = p->texture.height };

    return 0;
}

void player_update_velocity(Player* p, Input i, float gravity_velocity) {
    Vector2 targetVelocity = Vector2Zero();
    if (i.isLeftPressed) {
        targetVelocity.x += -PLAYER_HORIZOTNAL_SPEED;
    }
    if (i.isRightPressed) {
        targetVelocity.x += PLAYER_HORIZOTNAL_SPEED;
    }
    targetVelocity.y = p->velocity.y + gravity_velocity;
    p->velocity = targetVelocity;
}

void player_update_movement(Player* p, float dt) {
    p->position.x += p->velocity.x * dt;
    p->position.y += p->velocity.y * dt;
}

void player_draw(Player* p) {
    DrawTexture(p->texture, p->position.x, p->position.y, WHITE);
}

void player_destroy(Player* p) {
    if (IsTextureValid(p->texture)) {
        UnloadTexture(p->texture);
    }
}

void player_horizontal_collision_points(Player* p, Vector2** points, int* points_count, float dt) {
    // two points - middle left and middle right
    *points = (Vector2*)malloc(2 * sizeof(Vector2));
    if (*points == NULL) {
        *points_count = 0;
        return;
    }
    *points_count = 2;

    (*points)[0] = (Vector2){
        .x = p->position.x + p->velocity.x * dt,
        .y = p->position.y + p->dimensions.y / 2
    };
    (*points)[1] = (Vector2){
        .x = p->position.x + p->dimensions.x + p->velocity.x * dt,
        .y = p->position.y + p->dimensions.y / 2
    };
}

void player_vertical_collision_points(Player* p, Vector2** points, int* points_count, float dt) {
    // two points - lower left and lower right
    *points = malloc(2 * sizeof(Vector2));
    if (*points == NULL) {
        *points_count = 0;
        return;
    }
    *points_count = 2;
    (*points)[0] = (Vector2){
        .x = p->position.x,
        .y = p->position.y + p->dimensions.y + p->velocity.y * dt
    };
    (*points)[1] = (Vector2){
        .x = p->position.x + p->dimensions.x,
        .y = p->position.y + p->dimensions.y + p->velocity.y * dt
    };
}

void player_collision_points_destroy(Vector2* points) {
    free(points);
}
