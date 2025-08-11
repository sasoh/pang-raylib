#pragma once
#include <raylib.h>
#include <stdbool.h>

typedef enum {
    Layer_Level   = (1 << 0),
    Layer_Balloon = (1 << 1),
    Layer_Player  = (1 << 2),
    Layer_Weapon  = (1 << 3)
} Layer;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    Vector2 dimensions;
    int layer;
    bool is_gravity_applied;
    bool is_drawn;
} Entity;

int entity_init(Entity* e, Layer layer, bool is_gravity_applied, bool is_drawn, char *file_path);
void entity_update_movement(Entity* e, float dt);
void entity_update_gravity(Entity* e, float gravity_velocity);
void entity_draw(Entity* e);
void entity_destroy(Entity* e);