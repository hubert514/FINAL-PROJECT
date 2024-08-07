#include <stdio.h>
#include <stdint.h>
#include "set_character.h"
#include "back_pack.h"

int32_t init_player(s_player *player, char *player_name, int8_t gender)
{
    snprintf(player->name, 30, "%s", player_name);
    snprintf(player->kind, 10, "human");

    player->money = 0;
    player->hungry = 100;
    for (int i = 0; i < 100; i++)
    {
        player->back_pack[i].item_id = 0;
        snprintf(player->back_pack[i].item_name, 30, "none");
        snprintf(player->back_pack[i].item_pic, 100, "none");
        player->back_pack[i].item_health = 0;

    }
    return 0;
}

int32_t init_character(s_character *character, char *character_name, char *character_name_ch, char *kind, int32_t favorability, char *picture)
{
    snprintf(character->name, 30, "%s", character_name);
    snprintf(character->name_ch, 30, "%s", character_name_ch);
    snprintf(character->kind, 10, "%s", kind);
    character->favorability = favorability;
    snprintf(character->picture, 100, "%s", picture);
    printf("init_character [%s] success\n", character->name);
    return 0;
}
