// #pragma once
#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include "load_image.h"
#include "show_image.h"
#include "show_text.h"
#include <unistd.h>
#include <string.h>
#include "cp1.h"
#include "set_character.h"

int32_t cp1(char *chapter, char *player_name, int8_t player_gender)
{
    FILE *script = fopen("assets/script/script.toml", "r");
    if (script == NULL)
    {
        fprintf(stderr, "Error: Could not open script file\n");
        return -1;
    }

    char line[1000];

    // setting player
    s_player *player = calloc(1, sizeof(s_player));
    init_player(player, player_name, player_gender);
    // printf("%s, %s\n", player->name, player->kind);

    // setting characters
    s_character *characters = calloc(20, sizeof(s_character));
    set_character(&characters[EMPLOYER], "雇主", "獸人", 60);
    set_character(&characters[SHADOW_BLADE], "影刃", "半精靈", 30);
    set_character(&characters[SPRIT], "精靈", "精靈", 50);
    set_character(&characters[THIEF_LEADER], "盜賊領袖", "人類", -100);
    set_character(&characters[LEADER_OF_UBA], "聯合商業同盟會會長", "人類", 50);
    set_character(&characters[DRIVE_MAN], "馬車夫", "人類", 50);
    set_character(&characters[GUARD], "守衛隊長", "人類", 20);
    set_character(&characters[EMPIRE], "皇帝", "人類", 100);
    // for (int32_t i = 0; i < EMPIRE; i++)
    // {
    //     printf("%s, %s, %d\n", characters[i].name, characters[i].kind, characters[i].favorability);
    // }

    // set scene
    s_scene *scenes = calloc(5, sizeof(s_scene));
    snprintf(scenes[OFFICE].name, 20, "辦公室");
    snprintf(scenes[OFFICE].discription, 200, "典雅華麗，與外頭的暴亂形成對比");
    snprintf(scenes[FOREST].name, 20, "森林小徑");
    snprintf(scenes[FOREST].discription, 200, "幽暗，茂密，時時有奇怪聲音作響");
    snprintf(scenes[KINGDOM_ROAD].name, 20, "王國之路");
    snprintf(scenes[KINGDOM_ROAD].discription, 200, "萬里無雲，經過整修的寬闊，直線的石板路，邊界是森林");
    snprintf(scenes[PALACE].name, 20, "皇宮");
    snprintf(scenes[PALACE].discription, 200, "金碧輝煌，氣派非凡");

    while (fgets(line, sizeof(line), script))
    {
    }

    
    free(player);
    free(characters);
    free(scenes);
    fclose(script);
}

int main(int argc, char const *argv[])
{
    char *chapter = NULL;
    char player_name[] = "steve";
    cp1(chapter, player_name, 0);
    return 0;
}
