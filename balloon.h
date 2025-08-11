#pragma once
#include "entity.h"
#include <raylib.h>

#define BALLOON_TEXTURE_PATH "assets/balloon-01.png"
#define BALLOON_HORIZOTNAL_SPEED 400

typedef struct {
    Entity entity;
    float max_velocity;
} Balloon;

int balloon_init(Balloon* b, Vector2 position, bool initial_direction_right, float max_velocity);
void balloon_horizontal_collision_points(Balloon* b, Vector2** points, int* points_count, float dt);
void balloon_vertical_collision_points(Balloon* b, Vector2** points, int* points_count, float dt);
void balloon_collision_points_destroy(Vector2* points);
void balloon_horizontal_collision(Balloon* b);
void balloon_vertical_collision(Balloon* b);
void balloon_destroy(Balloon* b);