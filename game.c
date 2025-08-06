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

    return 0;
}

void game_draw(Game* g) {
    map_draw(&g->map);
    player_draw(&g->player);
}

void game_collision_check(Game* g, float dt) {
    Vector2 next_player_position = Vector2Add(g->player.position, Vector2Scale(g->player.velocity, dt));
    if (map_is_colliding_horizontal(&g->map, next_player_position, g->player.width)) {
        g->player.velocity.x = 0;
    }
    if (map_is_colliding_vertical(&g->map, next_player_position, g->player.height)) {
        g->player.velocity.y = 0;
    }
}

int game_loop(Game* g, Input i, float dt) {
    player_update_input(&g->player, i, GRAVITY_VELOCITY);
    game_collision_check(g, dt);
    player_update_movement(&g->player, dt);
    game_draw(g);
    return 0;
}

void game_destroy(Game* g) {
    map_destroy(&g->map);
    player_destroy(&g->player);
}