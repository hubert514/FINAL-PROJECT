#pragma once
#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "set_character.h"

int32_t show_back_pack(SDL_Renderer *renderer, TTF_Font *font, s_player player);

int32_t add_item(s_player *player, int8_t item_id, char *item_name, char *item_pic, int8_t item_health);

int32_t remove_item(s_player *player, int8_t item_id);