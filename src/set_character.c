#include <stdio.h>
#include <stdint.h>
#include "set_character.h"

int32_t init_player(s_player *player, char *player_name, int8_t gender)
{
    snprintf(player->name, 30, "%s", player_name);
    snprintf(player->kind, 10, "human");

    player->money = 0;
    player->hungry = 100;
    for (int i = 0; i < 100; i++)
    {
        player->back_pack[i] = 0;
    }
    return 0;
}

int32_t set_character(s_character *character, char *character_name, char *kind, int32_t favorability)
{
    snprintf(character->name, 30, "%s", character_name);
    snprintf(character->kind, 10, "%s", kind);
    character->favorability = favorability;
    return 0;
}