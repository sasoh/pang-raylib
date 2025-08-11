#include "entity.h"
#include <raymath.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int entity_init(Entity* e, Layer layer, bool is_gravity_applied, bool is_drawn, char* file_path) {
    e->position = (Vector2){ .x = 120, .y = 650 };
    e->velocity = Vector2Zero();

    if (file_path != NULL && strlen(file_path) > 0) {
        e->texture = LoadTexture(file_path);
        if (!IsTextureValid(e->texture)) {
            return EIO;
        }
    }

    e->dimensions = (Vector2){ .x = e->texture.width, .y = e->texture.height };
    e->layer = layer;
    e->is_gravity_applied = is_gravity_applied;
    e->is_drawn = is_drawn;

    return 0;
}

void entity_update_movement(Entity* e, float dt) {
    e->position = Vector2Add(e->position, Vector2Scale(e->velocity, dt));
}

void entity_update_gravity(Entity* e, float gravity_velocity) {
    if (!e->is_gravity_applied) return;
    e->velocity.y += gravity_velocity;
}

void entity_draw(Entity* e) {
    if (!e->is_drawn) return;
    if (!IsTextureValid(e->texture)) {
        fprintf(stderr, "Trying to draw entity with no texture.\n");
        return;
    }
    DrawTexture(e->texture, e->position.x, e->position.y, WHITE);
}

void entity_destroy(Entity* e) {
    if (IsTextureValid(e->texture)) {
        UnloadTexture(e->texture);
    }
}