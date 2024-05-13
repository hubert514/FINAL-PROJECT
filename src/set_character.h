#include <stdio.h>
#include <stdint.h>

typedef struct _s_player
{
    char name[30];
    char picture[100];
    char kind[10];
    int32_t money;
    int32_t hungry;
    int32_t back_pack[100];

} s_player;

typedef struct _s_character
{
    char name[30];
    char picture[100];
    char kind[10];
    int32_t favorability;
} s_character;

int32_t init_player(s_player *player, char *player_name, int8_t gender);


int32_t set_character(s_character *character, char *character_name, char *kind, int32_t favorability);