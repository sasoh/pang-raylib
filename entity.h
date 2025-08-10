#pragma once
#include <raylib.h>
#include <stdbool.h>

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    Vector2 dimensions;
    bool is_gravity_applied;
    bool is_drawn;
} Entity;

int entity_init(Entity* e, bool is_gravity_applied, bool is_drawn, char *file_path);
void entity_update_movement(Entity* e, float dt);
void entity_update_gravity(Entity* e, float gravity_velocity);
void entity_draw(Entity* e);
void entity_destroy(Entity* e);