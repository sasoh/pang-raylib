#include "map.h"
#include <errno.h>

Map current_map;

int game_init(void) {
    int load = map_load(&current_map);
    if (load == EIO) {
        return ENODATA;
    }

    return 0;
}

int game_loop(void) {
    map_draw(&current_map);
    return 0;
}

void game_destroy(void) {
    map_destroy(&current_map);
}