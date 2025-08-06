#include "player.h"
#include <errno.h>
#include <stdio.h>
#include <raymath.h>

int player_init(Player* p) {
    p->position = (Vector2) { .x = 150, .y = 100 };
    p->velocity = Vector2Zero();

    p->texture = LoadTexture(PLAYER_TEXTURE_PATH);
    if (!IsTextureValid(p->texture)) {
        return EIO;
    }

    p->size = 60;

    return 0;
}

void player_update_input(Player* p, Input i) {
    Vector2 targetVelocity = Vector2Zero();
    if (i.isLeftPressed) {
        targetVelocity.x += -PLAYER_HORIZOTNAL_SPEED;
    }
    if (i.isRightPressed) {
        targetVelocity.x += PLAYER_HORIZOTNAL_SPEED;
    }
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
    if (p == NULL) return;
    if (IsTextureValid(p->texture)) {
        UnloadTexture(p->texture);
    }
}