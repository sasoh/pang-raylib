#include "weapon.h"
#include <errno.h>
#include <raymath.h>

int weapon_init(Weapon* w) {
    int entity_init_status = entity_init(&w->entity, Layer_Weapon, false, false, PROJECTILE_TEXTURE_PATH);
    if (entity_init_status != 0) {
        return entity_init_status;
    }
    w->entity.velocity = (Vector2){ .x = 0.0, .y = -PROJECTILE_SPEED };
    w->is_shot = false;

    return 0;
}

void weapon_shoot(Weapon* w, Vector2 position) {
    w->entity.position = position;
    w->entity.is_drawn = true;
    w->is_shot = true;
}

void weapon_destroy(Weapon *w) {
    entity_destroy(&w->entity);
}