#include "player.h"
#include <errno.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

int player_init(Player* p) {
    int entity_init_status = entity_init(&p->entity, true, true, PLAYER_TEXTURE_PATH);
    if (entity_init_status != 0) {
        return entity_init_status;
    }
    p->entity.position = (Vector2){ .x = 120, .y = 650 };

    int weapon_init_status = weapon_init(&p->weapon);
    if (weapon_init_status != 0) {
        return weapon_init_status;
    }

    return 0;
}

void player_update_input(Player* p, Input i) {
    Vector2 targetVelocity = Vector2Zero();
    if (i.is_left_pressed) {
        targetVelocity.x += -PLAYER_HORIZOTNAL_SPEED;
    }
    if (i.is_right_pressed) {
        targetVelocity.x += PLAYER_HORIZOTNAL_SPEED;
    }
    targetVelocity.y = p->entity.velocity.y;
    p->entity.velocity = targetVelocity;

    if (i.is_shoot_pressed) {
        if (!p->weapon.is_shot) {
            weapon_shoot(
                &p->weapon,
                (Vector2){
                    .x = p->entity.position.x + p->entity.dimensions.x / 2,
                    .y = p->entity.position.y
                }
            );
        }
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
        .x = p->entity.position.x + p->entity.velocity.x * dt,
        .y = p->entity.position.y + p->entity.dimensions.y / 2
    };
    (*points)[1] = (Vector2){
        .x = p->entity.position.x + p->entity.dimensions.x + p->entity.velocity.x * dt,
        .y = p->entity.position.y + p->entity.dimensions.y / 2
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
        .x = p->entity.position.x,
        .y = p->entity.position.y + p->entity.dimensions.y + p->entity.velocity.y * dt
    };
    (*points)[1] = (Vector2){
        .x = p->entity.position.x + p->entity.dimensions.x,
        .y = p->entity.position.y + p->entity.dimensions.y + p->entity.velocity.y * dt
    };
}

void player_collision_points_destroy(Vector2* points) {
    free(points);
}
