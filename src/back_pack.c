#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "set_character.h"
#include "back_pack.h"
#include <SDL2/SDL_image.h>
#include "show_image.h"
#include "show_text.h"
#include <unistd.h>
#include <string.h>

int32_t show_back_pack(SDL_Renderer *renderer, TTF_Font *font, s_player player)
{
    char health[30];

    show_image(renderer, "assets/images/black.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    int32_t item_count = 0;

    for (int i = 0; i < 100; i++)
    {
        if (player.back_pack[i].item_id != 0)
        {
            show_text(renderer, player.back_pack[i].item_name, 150, 50 + item_count * 100, 48, font, (SDL_Color){255, 255, 255, 255});
            snprintf(health, 30, "損壞度: %d%%", player.back_pack[i].item_health);
            show_text(renderer, health, 150, 50 + item_count * 100 + 50, 48, font, (SDL_Color){255, 255, 255, 255});
            show_image(renderer, player.back_pack[i].item_pic, 50, 50 + item_count * 100, 90, 90);
            item_count++;
        }
    }
    if (item_count == 0)
    {
        show_text(renderer, "背包裡沒有物品", 50, 50, 48, font, (SDL_Color){255, 255, 255, 255});
    }
    show_text(renderer, "按b返回", 200, 50 + item_count * 100 + 50, 48, font, (SDL_Color){255, 255, 255, 255});
    

    SDL_Event event;
    while (1)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            return 1;
            break;
        }
        // if b is pressed
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
        {
            return 0;
            break;
        }
    }
    return 0;
}

int32_t add_item(s_player *player, int8_t item_id, char *item_name, char *item_pic, int8_t item_health)
{
    for (int i = 0; i < 100; i++)
    {
        if (player->back_pack[i].item_id == 0)
        {
            player->back_pack[i].item_id = item_id;
            snprintf(player->back_pack[i].item_name, 30, "%s", item_name);
            printf("%s, %s\n", item_name, player->back_pack[i].item_name);
            snprintf(player->back_pack[i].item_pic, 100, "%s", item_pic);
            player->back_pack[i].item_health = item_health;
            break;
        }
    }
    return 0;
}

int32_t remove_item(s_player *player, int8_t item_id)
{
    for (int i = 0; i < 100; i++)
    {
        if (player->back_pack[i].item_id == item_id)
        {
            player->back_pack[i].item_id = 0;
            snprintf(player->back_pack[i].item_name, 30, "none");
            snprintf(player->back_pack[i].item_pic, 100, "none");
            player->back_pack[i].item_health = 0;
            break;
        }
    }
    return 0;
}
