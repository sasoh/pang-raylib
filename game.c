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

int game_loop(Game* g) {
    map_draw(&g->map);
    player_draw(&g->player);
    return 0;
}

void game_destroy(Game* g) {
    if (g == NULL) return;
    map_destroy(&g->map);
    player_destroy(&g->player);
}