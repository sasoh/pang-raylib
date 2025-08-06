#include "game.h"
#include "map.h"
#include "player.h"
#include <errno.h>

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

void game_update_input(Game* g, Input i) {
    player_update_input(&g->player, i);
}

void game_update_movement(Game* g, float dt) {
    player_update_movement(&g->player, dt);
}

void game_draw(Game* g) {
    map_draw(&g->map);
    player_draw(&g->player);
}

int game_loop(Game* g, Input i, float dt) {
    game_update_input(g, i);
    game_update_movement(g, dt);
    game_draw(g);
    return 0;
}

void game_destroy(Game* g) {
    map_destroy(&g->map);
    player_destroy(&g->player);
}