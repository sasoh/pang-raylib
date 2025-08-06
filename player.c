#include "player.h"
#include <errno.h>
#include <raylib.h>
#include <stdio.h>

#define PLAYER_TEXTURE_PATH "assets/player-idle-01.png"

int player_init(Player* p) {
    p->position.x = 0;
    p->position.y = 0;
    
    p->texture = LoadTexture(PLAYER_TEXTURE_PATH);
    if (!IsTextureValid(p->texture)) {
        return EIO;
    }

    return 0;
}

void player_draw(Player* p) {
    DrawTexture(p->texture, p->position.x, p->position.y, WHITE);
}

void player_destroy(Player* p) {
    if (p == NULL) return;
    if (IsTextureValid(p->texture)) {
        UnloadTexture(p->texture);
    }
}