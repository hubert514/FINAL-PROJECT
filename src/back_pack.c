#pragma once
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

    show_image(renderer, "images/back_pack.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (player.back_pack[0].item_id == 0)
    {
        show_text(renderer, "No items in the backpack", 50, 50, 48, font, (SDL_Color){0, 0, 0, 255});
    }
    else
    {
        for (int i = 0; i < 100; i++)
        {
            if (player.back_pack[i].item_id != 0)
            {
                show_text(renderer, player.back_pack[i].item_name, 50, 50 + i * 100, 48, font, (SDL_Color){0, 0, 0, 255});
                snprintf(health, 30, "Health: %d", player.back_pack[i].item_health);
                show_text(renderer, health, 50, 50 + i * 100 + 50, 48, font, (SDL_Color){0, 0, 0, 255});
            }
        }
    }
    SDL_Event event;
    while (1)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            return 1;
            break;
        }
        // if esc is pressed
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                return 0;
                break;
            }
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
            snprintf(player->back_pack[i].item_name, 30, "");
            snprintf(player->back_pack[i].item_pic, 100, "");
            player->back_pack[i].item_health = 0;
            break;
        }
    }
    return 0;
}
