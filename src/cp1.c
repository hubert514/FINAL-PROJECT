// #pragma once
#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include "show_image.h"
#include "show_text.h"
#include <unistd.h>
#include <string.h>
#include "cp1.h"
#include "set_character.h"
#include "init.h"
#include <stdbool.h>

void show(SDL_Renderer *renderer, s_scene scene, s_character character, char *text, TTF_Font *font);
void set_scene(char *line, s_scene *now_scene, s_scene *scenes);
void set_character(char *line, s_character *now_character, s_character *characters);
void clear_events();
void display_options(SDL_Renderer *renderer, TTF_Font *font, s_options *options, int32_t option_num);

int32_t cp1(char *chapter, char *player_name, int8_t player_gender, SDL_Renderer *renderer, TTF_Font *font)
{
    // setup
    FILE *script = fopen("assets/script/script.toml", "r");
    if (script == NULL)
    {
        fprintf(stderr, "Error: Could not open script file\n");
        return -1;
    }

    char line[1000];

    // setting player
    s_player player;
    init_player(&player, player_name, player_gender);
    // printf("%s, %s\n", player.name, player.kind);

    // setting characters
    s_character characters[20];
    init_character(&characters[PLAYER], "player", player_name, player.kind, 0, "assets/images/character_boy.png");
    init_character(&characters[EMPLOYER], "employer", "雇主", "獸人", 60, "assets/images/sw.png");
    init_character(&characters[SHADOW_BLADE], "shadow_blade", "影刃", "半精靈", 30, "assets/images/sw.png");
    init_character(&characters[SPRIT], "sprit", "精靈", "精靈", 50, "assets/images/sw.png");
    init_character(&characters[THIEF_LEADER], "theif_leader", "盜賊領袖", "人類", -100, "assets/images/sw.png");
    init_character(&characters[LEADER_OF_UBA], "leader_of_UBA", "聯合商業同盟會會長", "人類", 50, "assets/images/sw.png");
    init_character(&characters[DRIVE_MAN], "drive_man", "馬車夫", "人類", 50, "assets/images/sw.png");
    init_character(&characters[GUARD], "guard", "守衛隊長", "人類", 20, "assets/images/sw.png");
    init_character(&characters[EMPIRE], "empire", "皇帝", "人類", 100, "assets/images/sw.png");
    // for (int32_t i = 0; i < EMPIRE; i++)
    // {
    //     printf("%s, %s, %d\n", characters[i].name, characters[i].kind, characters[i].favorability);
    // }

    // set scene
    s_scene scenes[5];
    snprintf(scenes[OFFICE].name, 20, "office");
    snprintf(scenes[OFFICE].name_ch, 20, "辦公室");
    snprintf(scenes[OFFICE].discription, 200, "典雅華麗，與外頭的暴亂形成對比");
    snprintf(scenes[OFFICE].file, 100, "assets/images/sw.jpg");
    snprintf(scenes[FOREST].name, 20, "forest");
    snprintf(scenes[FOREST].name_ch, 20, "森林小徑");
    snprintf(scenes[FOREST].discription, 200, "幽暗，茂密，時時有奇怪聲音作響");
    snprintf(scenes[FOREST].file, 100, "assets/images/sw.jpg");
    snprintf(scenes[KINGDOM_ROAD].name, 20, "kingdom_road");
    snprintf(scenes[KINGDOM_ROAD].name_ch, 20, "王國之路");
    snprintf(scenes[KINGDOM_ROAD].discription, 200, "萬里無雲，經過整修的寬闊，直線的石板路，邊界是森林");
    snprintf(scenes[KINGDOM_ROAD].file, 100, "assets/images/sw.jpg");
    snprintf(scenes[PALACE].name, 20, "palace");
    snprintf(scenes[PALACE].name_ch, 20, "皇宮");
    snprintf(scenes[PALACE].discription, 200, "金碧輝煌，氣派非凡");
    snprintf(scenes[PALACE].file, 100, "assets/images/sw.jpg");

    // test
    // show(renderer, scenes[OFFICE], characters[EMPIRE], "Hello, world!", font);
    // sleep(2);
    // end of setup

    // start of script
    SDL_Event event;
    bool quit = false, click_on_option = false;
    char now_text[1000];
    s_scene now_scene;
    s_character now_character;
    int32_t option_num = 0, mouse_x = 0, mouse_y = 0;
    char next[1000] = "cp1.begin", tmp[1000];
    s_options options[10];

    while (fgets(line, sizeof(line), script) && !quit)
    {
        // event quit

        if (line[0] == '#')
        {
            continue;
        }
        if (strstr(line, "scene ="))
        {
            set_scene(line, &now_scene, scenes);
        }
        if (strstr(line, "character ="))
        {
            set_character(line, &now_character, characters);
        }
        if (strstr(line, "text ="))
        {
            sscanf(line, "text = \"%[^\"]\"", now_text);
            show(renderer, now_scene, now_character, now_text, font);

            sleep(1);
            clear_events();

            while (1)
            {
                SDL_PollEvent(&event);
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                    break;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                {
                    clear_events();
                    break;
                }
                // if event == space
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                {
                    clear_events();
                    break;
                }
            }
        }
        if (strstr(line, "next ="))
        {
            sscanf(line, "next = \"%[^\"]\"", tmp);
            snprintf(next, 1002, "[%s]", tmp);
            printf("%s\n", next);
            fseek(script, 0, SEEK_SET);
            while (fgets(line, sizeof(line), script))
            {
                if (strstr(line, next))
                {
                    break;
                }
            }
        }
        // option
        if (strstr(line, "[["))
        {
            option_num = 0;
            while (fgets(line, sizeof(line), script))
            {
                if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0')
                {
                    break;
                }
                if (strstr(line, "option ="))
                {
                    sscanf(line, "option = \"%[^\"]\"", options[option_num].option);
                    printf("option%d: %s\n", option_num, options[option_num].option);
                }
                if (strstr(line, "next ="))
                {
                    sscanf(line, "next = \"%[^\"]\"", tmp);
                    snprintf(options[option_num].next, 1002, "[%s]", tmp);
                    printf("next%d: %s\n", option_num, options[option_num].next);
                    option_num++;
                }
            }
            // display options
            display_options(renderer, font, options, option_num);
            // wait for click
            while (1)
            {
                click_on_option = false;
                SDL_PollEvent(&event);
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                    break;
                }
                if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                {
                    mouse_x = event.button.x;
                    mouse_y = event.button.y;
                    for (int32_t i = 0; i < option_num; i++)
                    {
                        if (event.button.x >= 0 && event.button.x <= WINDOW_WIDTH && event.button.y >= 200 + i * 55 && event.button.y <= 200 + i * 55 + 50)
                        {
                            snprintf(next, 1002, "%s", options[i].next);
                            click_on_option = true;
                            break;
                        }
                    }
                    clear_events();
                }
                if (click_on_option)
                {
                    break;
                }
            }
            // find next
            fseek(script, 0, SEEK_SET);
            while (fgets(line, sizeof(line), script))
            {
                if (strstr(line, next))
                {
                    break;
                }
                // scene and character and 
                if (strstr(line, "scene ="))
                {
                    set_scene(line, &now_scene, scenes);
                }
                if (strstr(line, "character ="))
                {
                    set_character(line, &now_character, characters);
                }
                
            }
        }
        if (strstr(line, "end = 1"))
        {
            quit = true;
        }
        

        // if (line[0] == '[' && line[1] != '[')
        // {
        //     // refresh screen
        //     // SDL_RenderClear(renderer);
        //     // show_text(renderer, line, 0, 0, 50, font, (SDL_Color){255, 255, 255, 255});
        //     // till hit enter
        //     while (1)
        //     {
        //         SDL_PollEvent(&event);
        //         if (event.type == SDL_QUIT)
        //         {
        //             quit = true;
        //             break;
        //         }
        //         if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
        //         {
        //             break;
        //         }
        //         // if event == space
        //         if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
        //         {
        //             break;
        //         }

        //     }
        // }
    }

    fclose(script);
}

int main(int argc, char const *argv[])
{
    char *chapter = NULL;
    char player_name[] = "Steve";

    // init sdl
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int imgFlags;
    int32_t success = initialize_window(&window, &renderer, &imgFlags);
    TTF_Font *font = TTF_OpenFont("assets/fonts/kaiu.ttf", 24);
    if (font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }

    cp1(chapter, player_name, 0, renderer, font);

    // clean up
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void show(SDL_Renderer *renderer, s_scene scene, s_character character, char *text, TTF_Font *font)
{
    // refresh screen
    SDL_RenderClear(renderer);
    show_image(renderer, scene.file, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    show_image(renderer, character.picture, 0, 150, 400, 600);
    show_image(renderer, "assets/images/talk_block.png", 0, 600, WINDOW_WIDTH, 300);
    // printf("%s\n", character.name_ch);
    show_text(renderer, character.name_ch, 190, 620, 40, font, (SDL_Color){255, 255, 255, 255});
    show_text(renderer, text, 20, 730, 24, font, (SDL_Color){0, 0, 0, 255});

    return;
}

void set_scene(char *line, s_scene *now_scene, s_scene *scenes)
{
    // printf("%s\n", line);
    char scene_name[20];
    sscanf(line, "scene = \"%[^\"]\"", scene_name);
    // printf("%s\n", scene_name);
    for (int32_t i = 0; i < SCENE_NUM; i++)
    {
        // printf("%d, %s, %s\n", i, scene_name, scenes[i].name);
        if (strstr(scene_name, scenes[i].name))
        {
            // printf("set %s\n", scene_name);
            snprintf(now_scene->name, 20, "%s", scenes[i].name);
            snprintf(now_scene->name_ch, 20, "%s", scenes[i].name_ch);
            snprintf(now_scene->discription, 200, "%s", scenes[i].discription);
            snprintf(now_scene->file, 100, "%s", scenes[i].file);
            // printf("now: %s\n", now_scene->name);
            // printf("now: %s\n", now_scene->name_ch);
            // printf("now: %s\n", now_scene->discription);
            // printf("now: %s\n", now_scene->file);
            break;
        }
    }

    return;
}

void set_character(char *line, s_character *now_character, s_character *characters)
{
    char character_name[20];
    sscanf(line, "character = \"%[^\"]\"", character_name);
    for (int32_t i = 0; i < CHARACTER_NUM; i++)
    {
        if (strstr(character_name, characters[i].name))
        {
            snprintf(now_character->name, 30, "%s", character_name);
            snprintf(now_character->name_ch, 30, "%s", characters[i].name_ch);
            snprintf(now_character->kind, 20, "%s", characters[i].kind);
            snprintf(now_character->picture, 100, "%s", characters[i].picture);
            now_character->favorability = characters[i].favorability;
            // printf("now: %s\n", now_character->name);
            // printf("now: %s\n", now_character->kind);
            // printf("now: %s\n", now_character->picture);
            break;
        }
    }

    return;
}

void clear_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // 仅仅读取事件，而不做任何处理
    }
}

void display_options(SDL_Renderer *renderer, TTF_Font *font, s_options *options, int32_t option_num)
{
    for (int32_t i = 0; i < option_num; i++)
    {
        show_image(renderer, "assets/images/black.png", 0, 200 + i * 55, WINDOW_WIDTH, 50);
        // printf("%ld\n", strlen(options[i].option));
        show_text(renderer, options[i].option, 50, 200 + i * 55, 40, font, (SDL_Color){255, 255, 255, 255});
    }
}