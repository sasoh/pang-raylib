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

    for (int i = 0; i < BALLOON_COUNT; i++) {
        int balloon_load_status = balloon_init(
            &g->balloon[i],
            (Vector2){ .x = 220.0f + i * 200, .y = 150.0f },
            i % 2 == 0,
            GRAVITY_VELOCITY * 50
        );
        if (balloon_load_status == EIO) {
            return ENODATA;
        }
    }

    g->running_entities = malloc((2 + BALLOON_COUNT + g->map.rows * g->map.columns) * sizeof(Entity *));
    if (g->running_entities == NULL) {
        return ENOMEM;
    }
    
    int index = 0;
    (g->running_entities)[index++] = &g->player.entity;
    (g->running_entities)[index++] = &g->player.weapon.entity;
    for (int i = 0; i < BALLOON_COUNT; i++) {
        (g->running_entities)[index++] = &g->balloon[i].entity;
    }
    for (int i = 0; i < g->map.rows * g->map.columns; i++) {
        (g->running_entities)[index++] = &g->map.entities[i];
    }
    g->running_entities_count = index;

    return 0;
}

static void game_update_gravity(Game* g, float gravity_velocity) {   
    for (int i = 0; i < g->running_entities_count; i++) {
        entity_update_gravity(g->running_entities[i], gravity_velocity);
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
    balloon_collision_points_destroy(points);
    points = NULL;
    points_count = 0;

    for (int i = 0; i < BALLOON_COUNT; i++) {
        Balloon* b = &g->balloon[i];
        balloon_horizontal_collision_points(b, &points, &points_count, dt);
        for (int i = 0; i < points_count; i++) {
            if (map_check_collision(&g->map, points[i])) {
                balloon_horizontal_collision(b);
                break;
            }
        }
        balloon_collision_points_destroy(points);
        points = NULL;
        points_count = 0;

        balloon_vertical_collision_points(b, &points, &points_count, dt);
        for (int i = 0; i < points_count; i++) {
            if (map_check_collision(&g->map, points[i])) {
                balloon_vertical_collision(b);
                break;
            }
        }
        player_collision_points_destroy(points);
        points = NULL;
        points_count = 0;
    }
}

static void game_update_movement(Game* g, float dt) {
    for (int i = 0; i < g->running_entities_count; i++) {
        entity_update_movement(g->running_entities[i], dt);
    }
}

static void game_draw(Game* g) {
    for (int i = 0; i < g->running_entities_count; i++) {
        entity_draw(g->running_entities[i]);
    }
}

int game_loop(Game* g, Input i, float dt) {
    player_update_input(&g->player, i);
    game_update_gravity(g, GRAVITY_VELOCITY);
    game_collision_check(g, dt);
    game_update_movement(g, dt);
    game_draw(g);
    return 0;
}

void game_destroy(Game* g) {
    player_destroy(&g->player);
    for (int i = 0; i < BALLOON_COUNT; i++) {
        balloon_destroy(&g->balloon[i]);
    }
    map_destroy(&g->map);
    free(g->running_entities);
}