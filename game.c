#include "game.h"
#include "map.h"
#include "player.h"
#include <errno.h>
#include <raymath.h>

int game_init(Game* g) {
    int map_load_status = map_init(&g->map);
    if (map_load_status == EIO) {
        return ENODATA;
    }

    int player_load_status = player_init(&g->player);
    if (player_load_status == EIO) {
        return ENODATA;
    }

    g->balloon_count = 3;
    for (int i = 0; i < g->balloon_count; i++) {
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

    return 0;
}

static void game_update_velocity(Game* g, Input i, float gravity_velocity) {
    player_update_velocity(&g->player, i, gravity_velocity);
    for (int i = 0; i < g->balloon_count; i++) {
        balloon_update_velocity(&g->balloon[i], gravity_velocity);
    }
}

static void game_collision_check(Game* g, float dt) {
    Vector2* points = NULL;
    int points_count = 0;
    player_horizontal_collision_points(&g->player, &points, &points_count, dt);
    for (int i = 0; i < points_count; i++) {
        if (map_check_collision(&g->map, points[i])) {
            g->player.velocity.x = 0.0f;
            break;
        }
    }
    player_collision_points_destroy(points);
    points = NULL;
    points_count = 0;

    player_vertical_collision_points(&g->player, &points, &points_count, dt);
    for (int i = 0; i < points_count; i++) {
        if (map_check_collision(&g->map, points[i])) {
            g->player.velocity.y = 0.0f;
            break;
        }
    }
    balloon_collision_points_destroy(points);
    points = NULL;
    points_count = 0;

    for (int i = 0; i < g->balloon_count; i++) {
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
    player_update_movement(&g->player, dt);
    for (int i = 0; i < g->balloon_count; i++) {
        balloon_update_movement(&g->balloon[i], dt);
    }
}

static void game_draw(Game* g) {
    map_draw(&g->map);
    player_draw(&g->player);
    for (int i = 0; i < g->balloon_count; i++) {
        balloon_draw(&g->balloon[i]);
    }
}

int game_loop(Game* g, Input i, float dt) {
    game_update_velocity(g, i, GRAVITY_VELOCITY);
    game_collision_check(g, dt);
    game_update_movement(g, dt);
    game_draw(g);
    return 0;
}

void game_destroy(Game* g) {
    map_destroy(&g->map);
    player_destroy(&g->player);
    balloon_destroy(&g->balloon);
}