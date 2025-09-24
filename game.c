#include "game.h"
#include "map.h"
#include "player.h"
#include <errno.h>
#include <raymath.h>
#include <stdlib.h>

int game_init(Game* g) {
    int map_load_status = map_init(&g->map);
    if (map_load_status == EIO) {
        return ENODATA;
    }

    int player_load_status = player_init(&g->player);
    if (player_load_status == EIO) {
        return ENODATA;
    }

    g->balloons.head = NULL;
    for (int i = 0; i < BALLOON_COUNT; i++) {
        Balloon *balloon = malloc(sizeof(Balloon));
        int balloon_load_status = balloon_init(
            balloon,
            (Vector2){ .x = 220.0f + i * 200, .y = 150.0f },
            i % 2 == 0,
            12 * g->map.tile_size
        );
        if (balloon_load_status == EIO) {
            return ENODATA;
        }

        balloon_list_append(&g->balloons, balloon);
    }
    
    g->entities.head = NULL;
    entity_list_append(&g->entities, &g->player.entity);
    entity_list_append(&g->entities, &g->player.weapon.entity);
    for (int i = 0; i < g->map.rows * g->map.columns; i++) {
        entity_list_append(&g->entities, &g->map.entities[i]);
    }

    Balloon_list_node* balloon = g->balloons.head;
    entity_list_append(&g->entities, &balloon->balloon->entity);
    while ((balloon = balloon->next) != NULL) {
        entity_list_append(&g->entities, &balloon->balloon->entity);
    }

    return 0;
}

static void game_update_gravity(Game* g, float gravity_velocity) {   
    Entity_list_node* current = g->entities.head;
    while (current != NULL) {
        entity_update_gravity(current->entity, gravity_velocity);
        current = current->next;
    }
}

static void game_collision_check(Game* g, float dt) {
    Vector2* points = NULL;
    int points_count = 0;
    player_horizontal_collision_points(&g->player, &points, &points_count, dt);
    for (int i = 0; i < points_count; i++) {
        if (map_check_collision(&g->map, points[i])) {
            g->player.entity.velocity.x = 0.0f;
            break;
        }
    }
    player_collision_points_destroy(points);
    points = NULL;
    points_count = 0;

    player_vertical_collision_points(&g->player, &points, &points_count, dt);
    for (int i = 0; i < points_count; i++) {
        if (map_check_collision(&g->map, points[i])) {
            g->player.entity.velocity.y = 0.0f;
            break;
        }
    }
    player_collision_points_destroy(points);
    points = NULL;
    points_count = 0;

    Vector2 projectile_point = weapon_collision_point(&g->player.weapon, dt);
    
    Balloon_list_node* b = g->balloons.head;
    do {
        Balloon* balloon = b->balloon;
        if (g->player.weapon.is_shot) {
            if (ballon_has_projectile_collision(balloon, projectile_point)) {
                balloon_pop(balloon);
                weapon_stop(&g->player.weapon);
            }
        }

        balloon_horizontal_collision_points(balloon, &points, &points_count, dt);
        for (int i = 0; i < points_count; i++) {
            if (map_check_collision(&g->map, points[i])) {
                balloon_horizontal_collision(balloon);
                break;
            }
        }
        balloon_collision_points_destroy(points);
        points = NULL;
        points_count = 0;

        balloon_vertical_collision_points(balloon, &points, &points_count, dt);
        for (int i = 0; i < points_count; i++) {
            if (map_check_collision(&g->map, points[i])) {
                balloon_vertical_collision(balloon);
                break;
            }
        }
        player_collision_points_destroy(points);
        points = NULL;
        points_count = 0;
    } while ((b = b->next) != NULL);

    if (g->player.weapon.is_shot) {
        if (!map_check_within_boundaries(&g->map, projectile_point)) {
            weapon_stop(&g->player.weapon);
        }

        if (map_check_collision(&g->map, projectile_point)) {
            weapon_stop(&g->player.weapon);
        }
    }
}

static void game_update_movement(Game* g, float dt) {
    Entity_list_node* current = g->entities.head;
    while (current != NULL) {
        entity_update_movement(current->entity, dt);
        current = current->next;
    }
}

static void game_draw(Game* g) {
    Entity_list_node* current = g->entities.head;
    while (current != NULL) {
        entity_draw(current->entity);
        current = current->next;
    }
}

int game_loop(Game* g, Input i, float dt) {
    player_update_input(&g->player, i);
    game_update_gravity(g, GRAVITY_VELOCITY * dt);
    game_collision_check(g, dt);
    game_update_movement(g, dt);
    game_draw(g);
    return 0;
}

void game_destroy(Game* g) {
    player_destroy(&g->player);
    map_destroy(&g->map);
    entity_list_destroy(&g->entities);
    balloon_list_destroy(&g->balloons);
}