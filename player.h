#pragma once
#include <raylib.h>

typedef struct {
    Vector2 position;
    Texture2D texture;
} Player;

int player_init(Player* p);
void player_draw(Player* p);
void player_destroy(Player* p);