#pragma once
#include <raylib.h>

#define BALLOON_TEXTURE_PATH "assets/balloon-01.png"
#define BALLOON_HORIZOTNAL_SPEED 200

typedef struct {
   Texture2D texture;
   Vector2 position;
   Vector2 velocity;
   Vector2 dimensions;
} Balloon;

int balloon_init(Balloon* b);
void balloon_update_velocity(Balloon* b, float gravity_velocity);
void balloon_update_movement(Balloon* b, float dt);
void balloon_draw(Balloon* b);
void balloon_destroy(Balloon *b);