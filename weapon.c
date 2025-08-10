#include "weapon.h"
#include <errno.h>
#include <raymath.h>

int weapon_init(Weapon* w) {
    w->position = Vector2Zero();
    w->velocity = (Vector2){ .x = 0.0, .y = -PROJECTILE_SPEED };

    w->texture = LoadTexture(PROJECTILE_TEXTURE_PATH);
    if (!IsTextureValid(w->texture)) {
        return EIO;
    }

    w->dimensions = (Vector2){ .x = w->texture.width, .y = w->texture.height };
    w->is_shot = false;

    return 0;
}

void weapon_shoot(Weapon* w, Vector2 position) {
    w->position = position;
    w->is_shot = true;
}

void weapon_update_movement(Weapon* w, float dt) {
    if (w->is_shot == false) return;
    w->position.x += w->velocity.x * dt;
    w->position.y += w->velocity.y * dt;
}

void weapon_draw(Weapon* w) {
    if (w->is_shot == false) return;
    DrawTexture(w->texture, w->position.x, w->position.y, WHITE);
}

void weapon_destroy(Weapon* w) {
    if (IsTextureValid(w->texture)) {
        UnloadTexture(w->texture);
    }
}