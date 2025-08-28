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
    if (w->is_shot) return;
    w->entity.position = position;
    w->entity.is_drawn = true;
    w->is_shot = true;
}

Vector2 weapon_collision_point(Weapon* w, float dt)
{
    return w->entity.position;
}

void weapon_stop(Weapon* w)
{
    w->is_shot = false;
    w->entity.is_drawn = false;
}

void weapon_destroy(Weapon *w) {
    entity_destroy(&w->entity);
}