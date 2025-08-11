#include "balloon.h"
#include <errno.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

int balloon_init(Balloon* b, Vector2 position, bool intial_direction_right, float max_velocity) {
    int entity_init_status = entity_init(&b->entity, Layer_Balloon, true, true, BALLOON_TEXTURE_PATH);
    if (entity_init_status != 0) {
        return entity_init_status;
    }

    b->entity.position = position;
    int direction_multiplier = intial_direction_right ? 1 : -1;
    b->entity.velocity = (Vector2){ .x = direction_multiplier * BALLOON_HORIZOTNAL_SPEED, .y = 0.0f };
    b->max_velocity = max_velocity;

    return 0;
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
        .x = b->entity.position.x + b->entity.velocity.x * dt,
        .y = b->entity.position.y + b->entity.dimensions.y / 2
    };
    (*points)[1] = (Vector2){
        .x = b->entity.position.x + b->entity.velocity.x * dt + b->entity.dimensions.x,
        .y = b->entity.position.y + b->entity.dimensions.y / 2
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
        .x = b->entity.position.x + b->entity.dimensions.x / 2,
        .y = b->entity.position.y + b->entity.velocity.y * dt
    };
    (*points)[1] = (Vector2){
        .x = b->entity.position.x + b->entity.dimensions.x / 2,
        .y = b->entity.position.y + b->entity.velocity.y * dt + b->entity.dimensions.y
    };
}

void balloon_collision_points_destroy(Vector2* points) {
    free(points);
}

void balloon_horizontal_collision(Balloon* b) {
    b->entity.velocity.x *= -1;
}

void balloon_vertical_collision(Balloon* b) {
    b->entity.velocity.y = Clamp(-1 * b->entity.velocity.y, -b->max_velocity, b->max_velocity);
}

void balloon_destroy(Balloon *b) {
    entity_destroy(&b->entity);
}