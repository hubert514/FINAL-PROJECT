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
#include "playSound.h"
#include "back_pack.h"
#include "show_GIF.h"

void show(SDL_Renderer *renderer, s_scene scene, s_character character, char *text, TTF_Font *font, s_player *player);
void set_scene(char *line, s_scene *now_scene, s_scene *scenes);
void set_character(char *line, s_character *now_character, s_character *characters);
void clear_events();
void display_options(SDL_Renderer *renderer, TTF_Font *font, s_options *options, int32_t option_num);
int32_t utf8_char_len(const char *s);
void set_faverability(char *line, s_character *characters);
void get_item(s_player *player, char *line, s_item *items);
void save(s_player player, s_character *characters, s_scene *scenes, s_scene now_scene, s_character now_character, char *line, char *next);
void load_data(s_player *player, s_character *characters, s_scene *scenes, s_scene *now_scene, s_character *now_character, char *line, char *next);
void print_data(s_player player, s_character *characters, s_scene *scenes, s_scene now_scene, s_character now_character, char *line, char *next);
void init_item(s_item *item, int8_t item_id, char *item_name, char *item_pic, int8_t item_health);

int32_t cp1(int8_t load, char *player_name, int8_t player_gender, SDL_Renderer *renderer, TTF_Font *font)
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
    char player_gender_pic[100];

    snprintf(player_gender_pic, 100, "assets/images/character_player.png");

    // printf("%s, %s\n", player.name, player.kind);
    // init
    while (fgets(line, sizeof(line), script))
    {
        if (strstr(line, "init = 1"))
        {
            break;
        }
    }

    // setting characters
    s_character characters[20];
    // initcharacters

    init_character(&characters[PLAYER], "player", player_name, player.kind, 0, player_gender_pic);
    // if read "init_character"
    // read [set_character]
    while (fgets(line, sizeof(line), script))
    {
        if (strstr(line, "[end_of_set_character]"))
        {
            printf("end of set character\n");
            break;
        }
        if (strstr(line, "[[init_character]]"))
        {
            // set_character = 0
            // character = "employer"
            // name = "雇主(冒險家協會會長)"
            // kind = "人類"
            // Favorability = 60
            // pic = "assets/images/employer_normal.png"
            int32_t set_character = 0;
            char name[100], kind[100], pic[100], name_ch[100];
            int32_t favorability = 0;

            fgets(line, sizeof(line), script);
            sscanf(line, "set_character = %d", &set_character);
            fgets(line, sizeof(line), script);
            sscanf(line, "character = \"%[^\"]\"", name);
            fgets(line, sizeof(line), script);
            sscanf(line, "name = \"%[^\"]\"", name_ch);
            fgets(line, sizeof(line), script);
            sscanf(line, "kind = \"%[^\"]\"", kind);
            fgets(line, sizeof(line), script);
            sscanf(line, "Favorability = %d", &favorability);
            fgets(line, sizeof(line), script);
            sscanf(line, "pic = \"%[^\"]\"", pic);
            init_character(&characters[set_character], name, name_ch, kind, favorability, pic);
        }
    }
    // test
    // for (int32_t i = 0; i < CHARACTER_NUM; i++)
    // {
    //     printf("%s, %s, %s, %d, %s\n", characters[i].name, characters[i].name_ch, characters[i].kind, characters[i].favorability, characters[i].picture);
    // }

    // init_character(&characters[EMPLOYER], "employer", "雇主(冒險家協會會長)", "人類", 60, "assets/images/employer_normal.png");
    // init_character(&characters[SHADOW_BLADE], "shadow_blade", "影刃", "半精靈", 30, "assets/images/shadow_blade.png");
    // init_character(&characters[SPRIT], "sprit", "精靈", "精靈", 50, "assets/images/sprit.png");
    // init_character(&characters[THIEF_LEADER], "theif_leader", "盜賊領袖", "人類", -100, "assets/images/gurad.png");
    // init_character(&characters[LEADER_OF_UBA], "leader_of_UBA", "聯合商業同盟會會長", "人類", 50, "assets/images/guard.png");
    // init_character(&characters[DRIVE_MAN], "drive_man", "馬車夫", "人類", 50, "assets/images/driveman.png");
    // init_character(&characters[GUARD], "guard", "守衛隊長", "人類", 20, "assets/images/guard.png");
    // init_character(&characters[EMPIRE], "empire", "皇帝", "人類", 100, "assets/images/empire.png");
    // init_character(&characters[OLD_MAN], "old_man", "老人", "人類", 50, "assets/images/oldman.png");
    // for (int32_t i = 0; i < EMPIRE; i++)
    // {
    //     printf("%s, %s, %d\n", characters[i].name, characters[i].kind, characters[i].favorability);
    // }

    // set scene
    s_scene scenes[5];
    // snprintf(scenes[OFFICE].name, 20, "office");
    // snprintf(scenes[OFFICE].name_ch, 20, "辦公室");
    // snprintf(scenes[OFFICE].discription, 200, "典雅華麗，與外頭的暴亂形成對比");
    // snprintf(scenes[OFFICE].file, 100, "assets/images/office.png");
    // snprintf(scenes[FOREST].name, 20, "forest");
    // snprintf(scenes[FOREST].name_ch, 20, "森林小徑");
    // snprintf(scenes[FOREST].discription, 200, "幽暗，茂密，時時有奇怪聲音作響");
    // snprintf(scenes[FOREST].file, 100, "assets/images/forest.png");
    // snprintf(scenes[KINGDOM_ROAD].name, 20, "kingdom_road");
    // snprintf(scenes[KINGDOM_ROAD].name_ch, 20, "王國之路");
    // snprintf(scenes[KINGDOM_ROAD].discription, 200, "萬里無雲，經過整修的寬闊，直線的石板路，邊界是森林");
    // snprintf(scenes[KINGDOM_ROAD].file, 100, "assets/images/sw.jpg");
    // snprintf(scenes[PALACE].name, 20, "palace");
    // snprintf(scenes[PALACE].name_ch, 20, "皇宮");
    // snprintf(scenes[PALACE].discription, 200, "金碧輝煌，氣派非凡");
    // snprintf(scenes[PALACE].file, 100, "assets/images/palace.png");
    while (fgets(line, sizeof(line), script))
    {
        if (strstr(line, "[end_of_set_scene]"))
        {
            printf("end of set scene\n");
            break;
        }
        if (strstr(line, "[[init_scene]]"))
        {
            // set_scene = 0
            // scene = "office"
            // name = "辦公室"
            // description = "典雅華麗，與外頭的暴亂形成對比"
            // pic = "assets/images/office.png"
            // enter = "assets/images/to_office.png"
            // left = "assets/images/left_office.png"
            int32_t set_scene = 0;
            char name[20], name_ch[20], pic[100], description[200], entergif[100], leftgif[100];

            fgets(line, sizeof(line), script);
            sscanf(line, "set_scene = %d", &set_scene);
            fgets(line, sizeof(line), script);
            sscanf(line, "scene = \"%[^\"]\"", name);
            fgets(line, sizeof(line), script);
            sscanf(line, "name = \"%[^\"]\"", name_ch);
            fgets(line, sizeof(line), script);
            sscanf(line, "description = \"%[^\"]\"", description);
            fgets(line, sizeof(line), script);
            sscanf(line, "pic = \"%[^\"]\"", pic);
            fgets(line, sizeof(line), script);
            sscanf(line, "enter = \"%[^\"]\"", entergif);
            fgets(line, sizeof(line), script);
            sscanf(line, "left = \"%[^\"]\"", leftgif);
            snprintf(scenes[set_scene].name, 20, "%s", name);
            snprintf(scenes[set_scene].name_ch, 20, "%s", name_ch);
            snprintf(scenes[set_scene].discription, 200, "%s", description);
            snprintf(scenes[set_scene].file, 100, "%s", pic);
            snprintf(scenes[set_scene].entergif, 100, "%s", entergif);
            snprintf(scenes[set_scene].leftgif, 100, "%s", leftgif);

            printf("%s, %s, %s, %s, %s, %s\n", scenes[set_scene].name, scenes[set_scene].name_ch, scenes[set_scene].discription, scenes[set_scene].file, scenes[set_scene].entergif, scenes[set_scene].leftgif);
        }
    }
    {
        /* code */
    }

    // init_item
    s_item items[100];

    while (fgets(line, sizeof(line), script))
    {
        if (strstr(line, "[end_of_set_item]"))
        {
            printf("end of set item\n");
            break;
        }
        if (strstr(line, "[[init_item]]"))
        {
            // item_id = 1
            // name = "斧頭"
            // pic = "assets/images/axe.png"
            // health = 50
            int8_t item_id = 0, health = 0;
            char name[20], pic[100];

            fgets(line, sizeof(line), script);
            sscanf(line, "item_id = %hhd", &item_id);
            fgets(line, sizeof(line), script);
            sscanf(line, "name = \"%[^\"]\"", name);
            fgets(line, sizeof(line), script);
            sscanf(line, "pic = \"%[^\"]\"", pic);
            fgets(line, sizeof(line), script);
            sscanf(line, "health = %hhd", &health);
            init_item(&items[item_id], item_id, name, pic, health);

            printf("%d, %s, %s, %d\n", items[item_id].item_id, items[item_id].item_name, items[item_id].item_pic, items[item_id].item_health);
        }
    }

    // test
    // show(renderer, scenes[OFFICE], characters[EMPIRE], "Hello, world!", font);
    // sleep(2);
    // end of setup

    // start of script
    SDL_Event event;
    bool quit = false, click_on_option = false, fight_win = false;
    char now_text[1000];
    s_scene now_scene;
    snprintf(now_scene.name, 20, "n");
    s_character now_character;
    int32_t option_num = 0, mouse_x = 0, mouse_y = 0;
    char next[1000] = "cp1.begin", tmp[1000];
    s_options options[10];
    int32_t mission_pay = 0;
    int32_t return_type = 0;
    bool seek_hungry = false;

    show_image(renderer, "assets/images/black.png", 200, 200, WINDOW_WIDTH - 400, WINDOW_HEIGHT - 400);
    show_text(renderer, "遊戲開始", 200, 350, 150, font, (SDL_Color){255, 255, 255, 255});
    playSound("assets/sound/enter_game.wav", 1000);
    // printf("playsound\n");
    // fseek(script, 0, SEEK_SET);
    // printf("playsound\n");
    fseek(script, 0, SEEK_SET);
    while (fgets(line, sizeof(line), script))
    {
        if (strstr(line, "[story_start]"))
        {
            fgets(line, sizeof(line), script);
            sscanf(line, "next = \"%[^\"]\"", tmp);
            snprintf(next, 1002, "[%s]", tmp);
            printf("%s\n", next);
            break;
        }
    }

    while (fgets(line, sizeof(line), script) && !quit)
    {
        // check load
        if (load)
        {
            // load all data
            load_data(&player, characters, scenes, &now_scene, &now_character, line, next);
            print_data(player, characters, scenes, now_scene, now_character, line, next);
            load = 0;
            // find next
            fseek(script, 0, SEEK_SET);
            while (fgets(line, sizeof(line), script))
            {
                if (strstr(line, next))
                {
                    break;
                }
            }
        }
        if (player.hungry <= 0 && !seek_hungry)
        {
            snprintf(next, 1002, "[end.dead_by_hungry]");
            fseek(script, 0, SEEK_SET);
            while (fgets(line, sizeof(line), script))
            {
                if (strstr(line, next))
                {
                    seek_hungry = true;
                    break;
                }
            }
        }

        // event quit

        if (line[0] == '#')
        {
            continue;
        }
        if (strstr(line, "scene ="))
        {
            if (!strstr(line, now_scene.name) || strlen(now_scene.name) < 2)
            {
                for (int32_t i = 0; i < SCENE_NUM; i++)
                {
                    if (strstr(now_scene.name, scenes[i].name) && strlen(scenes[i].leftgif) > 2)
                    {
                        printf("left %s", scenes[i].leftgif);
                        displayGif(renderer, scenes[i].leftgif);
                        break;
                    }
                }

                set_scene(line, &now_scene, scenes);
                if (strstr(now_scene.name, "kingdom_road"))
                {
                    printf("%s\n", now_scene.name);
                    show_image(renderer, "assets/images/black.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                    show_text(renderer, "由於僱用不到馬車夫，所以你只能走森林小徑", 20, 20, 50, font, (SDL_Color){255, 255, 255, 255});
                    show_text(renderer, "按下空白繼續", 1000, WINDOW_HEIGHT - 50, 24, font, (SDL_Color){255, 255, 255, 255});
                    set_scene("scene = \"forest\"", &now_scene, scenes);
                    sleep(0.25);
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
                            playSound("assets/sound/sound.wav", 1000);
                            printf("playsound\n");
                            clear_events();
                            break;
                        }
                        // if event == B
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
                        {
                            if (show_back_pack(renderer, font, player))
                            {
                                quit = true;
                                break;
                            }
                            show(renderer, now_scene, now_character, now_text, font, &player);
                            clear_events();
                        }
                        // if esc is pressed
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            clear_events();
                            show_image(renderer, "assets/images/esc.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                            // if esc is pressed again
                            while (1)
                            {
                                SDL_PollEvent(&event);
                                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                                {
                                    break;
                                }
                                // if e is pressed
                                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
                                {
                                    quit = true;
                                    return_type = 1;
                                    break;
                                }
                                // if s is pressed
                                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
                                {
                                    // save_system
                                    // save all data
                                    save(player, characters, scenes, now_scene, now_character, line, next);
                                    show_image(renderer, "assets/images/black.png", 200, 200, WINDOW_WIDTH - 400, WINDOW_HEIGHT - 400);
                                    show_text(renderer, "Saved", 200, 350, 150, font, (SDL_Color){255, 255, 255, 255});
                                    sleep(1);
                                    show_image(renderer, "assets/images/esc.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                                }
                            }
                            show(renderer, now_scene, now_character, now_text, font, &player);
                            clear_events();
                        }
                        if (quit)
                        {
                            break;
                        }
                    }

                    // next = cp2.forrest
                    snprintf(next, 1002, "[cp2.forest]");
                    fseek(script, 0, SEEK_SET);
                    while (fgets(line, sizeof(line), script))
                    {
                        if (strstr(line, next))
                        {
                            break;
                        }
                    }
                }

                for (int32_t i = 0; i < SCENE_NUM; i++)
                {
                    if (strstr(now_scene.name, scenes[i].name) && strlen(scenes[i].entergif) > 2)
                    {
                        printf("ender %s", scenes[i].entergif);
                        displayGif(renderer, scenes[i].entergif);
                        break;
                    }
                }
            }
            else
            {
                printf("same scene\n");
                printf("%s\n", now_scene.name);
            }
        }
        if (strstr(line, "character ="))
        {
            set_character(line, &now_character, characters);
        }
        if (strstr(line, "text ="))
        {
            sscanf(line, "text = \"%[^\"]\"", now_text);
            show(renderer, now_scene, now_character, now_text, font, &player);

            sleep(0.25);
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
                    playSound("assets/sound/sound.wav", 1000);
                    printf("playsound\n");
                    clear_events();
                    break;
                }
                // if event == B
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
                {
                    if (show_back_pack(renderer, font, player))
                    {
                        quit = true;
                        break;
                    }
                    show(renderer, now_scene, now_character, now_text, font, &player);
                    clear_events();
                }
                // if esc is pressed
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                {
                    clear_events();
                    show_image(renderer, "assets/images/esc.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                    // if esc is pressed again
                    while (1)
                    {
                        SDL_PollEvent(&event);
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            break;
                        }
                        // if e is pressed
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
                        {
                            quit = true;
                            return_type = 1;
                            break;
                        }
                        // if s is pressed
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
                        {
                            // save_system
                            // save all data
                            save(player, characters, scenes, now_scene, now_character, line, next);
                            show_image(renderer, "assets/images/black.png", 200, 200, WINDOW_WIDTH - 400, WINDOW_HEIGHT - 400);
                            show_text(renderer, "Saved", 200, 350, 150, font, (SDL_Color){255, 255, 255, 255});
                            sleep(1);
                            show_image(renderer, "assets/images/esc.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                        }
                    }
                    show(renderer, now_scene, now_character, now_text, font, &player);
                    clear_events();
                }
                if (quit)
                {
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
                            playSound("assets/sound/click.wav", 550);
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
                // if (strstr(line, "scene ="))
                // {
                //     set_scene(line, &now_scene, scenes);
                // }
                if (strstr(line, "character ="))
                {
                    set_character(line, &now_character, characters);
                }
            }
        }
        if (strstr(line, "Favorability ="))
        {
            printf("setting favorability\n");
            set_faverability(line, characters);
            printf("Favorability: %d\n", characters[EMPLOYER].favorability);
            if (characters[EMPLOYER].favorability == 70)
            {
                // happy
                printf("happy\n");
                init_character(&characters[EMPLOYER], "employer", "雇主", "獸人", 70, "assets/images/employer_normal.png");
            }
            else if (characters[EMPLOYER].favorability == 50)
            {
                // normal
                printf("normal\n");
                init_character(&characters[EMPLOYER], "employer", "雇主", "獸人", 50, "assets/images/employer_unhappy.png");
            }
            else if (characters[EMPLOYER].favorability == 30)
            {
                // angry
                printf("angry\n");
                init_character(&characters[EMPLOYER], "employer", "雇主", "獸人", 30, "assets/images/employer_superunhappy.png");
            }

            set_character(line, &now_character, characters);
        }

        if (strstr(line, "[cp1.mission_equipment_get]"))
        {
            set_character("character = \"employer\"", &now_character, characters);
            if (characters[EMPLOYER].favorability >= 70)
            {
                snprintf(now_text, 1000, "年輕人，不要吝於請求，我手頭正好有隻我珍藏的斧頭(折舊50%%)，雖然有點舊了，但還堪用，希望對你的旅程有所幫助");
                // get 斧頭
                add_item(&player, 1, "斧頭", "assets/images/axe.png", 50);
            }
            if (characters[EMPLOYER].favorability < 70 && characters[EMPLOYER].favorability > 30)
            {
                snprintf(now_text, 1000, "對了，我手頭正好有張順手的弓(折舊75%%)，但沒有箭矢，你就湊合著用吧");
                // get 弓
                add_item(&player, 2, "弓", "assets/images/bow.png", 75);
            }
            if (characters[EMPLOYER].favorability <= 30)
            {
                snprintf(now_text, 1000, "我想，憑你的本事，幾隻哥布林應該可以赤手空拳解決吧，跟一個你所謂的「中年獸人」請求武器是多麼沒出息的行為阿");

                // get nothing
            }

            show(renderer, now_scene, now_character, now_text, font, &player);
            sleep(0.25);
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
                    playSound("assets/sound/sound.wav", 1000);
                    printf("playsound\n");
                    clear_events();
                    break;
                }
                // if event == B
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
                {
                    if (show_back_pack(renderer, font, player))
                    {
                        quit = true;
                        break;
                    }
                    show(renderer, now_scene, now_character, now_text, font, &player);
                    clear_events();
                }
                // if esc is pressed
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                {
                    clear_events();
                    show_image(renderer, "assets/images/esc.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                    // if esc is pressed again
                    while (1)
                    {
                        SDL_PollEvent(&event);
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            break;
                        }
                        // if e is pressed
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
                        {
                            quit = true;
                            return_type = 1;
                            break;
                        }
                        // if s is pressed
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
                        {
                            // save_system
                            // save all data
                            save(player, characters, scenes, now_scene, now_character, line, next);
                            show_image(renderer, "assets/images/black.png", 200, 200, WINDOW_WIDTH - 400, WINDOW_HEIGHT - 400);
                            show_text(renderer, "Saved", 200, 350, 150, font, (SDL_Color){255, 255, 255, 255});
                            sleep(1);
                            show_image(renderer, "assets/images/esc.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                        }
                    }
                    show(renderer, now_scene, now_character, now_text, font, &player);
                    clear_events();
                }
                if (quit)
                {
                    break;
                }
            }
            while (fgets(line, sizeof(line), script))
            {
                if (strstr(line, "getequip = \"end\""))
                {
                    break;
                }
            }
        }
        if (strstr(line, "get_pay ="))
        {
            mission_pay = atoi(&line[10]);
            printf("mission pay set: %d\n", mission_pay);
        }
        if (strstr(line, "get_money = \"get_pay\""))
        {
            player.money += mission_pay;
            printf("get pay money: %d\n", player.money);
        }
        if (strstr(line, "player.hungry ="))
        {
            if (line[16] == '+')
            {
                player.hungry += atoi(&line[17]);
                printf("player hungry: %d\n", player.hungry);
            }
            else if (line[16] == '-')
            {
                player.hungry -= atoi(&line[17]);
                printf("player hungry: %d\n", player.hungry);
            }
            else
            {
                player.hungry = atoi(&line[16]);
                printf("player hungry: %d\n", player.hungry);
            }
            printf("player hungry: %d\n", player.hungry);
        }
        if (strstr(line, "get ="))
        {
            get_item(&player, line, items);
        }
        int32_t money = 0;
        int8_t fix_option = 0;
        if (strstr(line, "[cp2.about_weapon_answer]"))
        {
            now_character = characters[SHADOW_BLADE];
            if (characters[EMPLOYER].favorability == 70)
            {
                snprintf(now_text, 1000, "手頭的武器?喔你是說這把斧頭嗎?嗯...斧柄的部分確實看起來舊了點，使用的是北方的橡木，質地輕卻夠堅韌...這樣好了，你給我10個金幣，我剛好有修過斧頭的經驗(折舊度-30%%)，材料我也剛好有，這粗活就由我替你代勞吧，不知您意下如何?");
                money = 10;
                fix_option = 1;
                show(renderer, now_scene, now_character, now_text, font, &player);
            }
            if (characters[EMPLOYER].favorability == 50)
            {
                snprintf(now_text, 1000, "手頭的武器?喔你是說這個沒有箭矢的弓嗎?嗯...我看看...彈性不太好，但彈性還可以...兄弟你可能走運了，雖然我無法強化這個弓的性能，但只要你支付給我20個金幣，我願意提供你五支上好的箭矢，省著點用吧");
                money = 20;
                fix_option = 2;
                show(renderer, now_scene, now_character, now_text, font, &player);
            }
            if (characters[EMPLOYER].favorability == 30)
            {
                snprintf(now_text, 1000, "手頭的武器?喔你是說你的拳頭嗎?嗯...表面粗糙，關節處磨損有長繭...這確實是你僅剩的武器了呀哈哈，好啦我手上剛好有支2尺3吋的開山刀(折舊度20%%)，只要你支付30個金幣他就歸你了");
                money = 30;
                fix_option = 3;
                show(renderer, now_scene, now_character, now_text, font, &player);
            }

            // option
            option_num = 2;
            snprintf(options[0].option, 100, "同意");
            snprintf(options[0].next, 100, "cp2.about_weapon_answer.agree");
            snprintf(options[1].option, 100, "拒絕");
            snprintf(options[1].next, 100, "cp2.about_weapon_answer.refuse");
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
                            snprintf(next, 1002, "[%s]", options[i].next);
                            playSound("assets/sound/click.wav", 550);
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
            if (strstr(next, "cp2.about_weapon_answer.agree"))
            {
                player.money -= money;
                if (fix_option == 1)
                {
                    remove_item(&player, 1);
                    add_item(&player, 1, "斧頭", "assets/images/axe.png", 20);
                }
                if (fix_option == 2)
                {
                    // add arrow
                    add_item(&player, 5, "箭矢X5", "assets/images/arrow.png", 0);
                }
                if (fix_option == 3)
                {
                    remove_item(&player, 2);
                    add_item(&player, 6, "開山刀", "assets/images/machete.png", 80);
                }
            }
            // find next
            snprintf(next, 1000, "[cp2.question_about_shadow]");
            fseek(script, 0, SEEK_SET);
            while (fgets(line, sizeof(line), script))
            {
                if (strstr(line, next))
                {
                    break;
                }
                // scene and character and
                // if (strstr(line, "scene ="))
                // {
                //     set_scene(line, &now_scene, scenes);
                // }
                if (strstr(line, "character ="))
                {
                    set_character(line, &now_character, characters);
                }
            }
        }

        if (strstr(line, "[cp2.shadow_blade_fight]"))
        {
            // characters[EMPLOYER].favorability = 50;// for test
            show(renderer, now_scene, characters[SHADOW_BLADE], now_text, font, &player);
            option_num = 1;
            if (characters[EMPLOYER].favorability == 70)
            {
                snprintf(options[0].option, 100, "從背包掏出斧頭");
                snprintf(options[0].next, 100, "cp2.fight_with_axe");
            }
            else if (characters[EMPLOYER].favorability == 50)
            {
                snprintf(options[0].option, 100, "從背包掏出沒有箭矢的弓");
                snprintf(options[0].next, 100, "cp2.fight_with_bow");
            }
            else
            {
                snprintf(options[0].option, 100, "直接使用拳頭");
                snprintf(options[0].next, 100, "cp2.fight_with_fist");
            }
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
                            snprintf(next, 1002, "[%s]", options[i].next);
                            playSound("assets/sound/click.wav", 550);
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
                // if (strstr(line, "scene ="))
                // {
                //     set_scene(line, &now_scene, scenes);
                // }
                if (strstr(line, "character ="))
                {
                    set_character(line, &now_character, characters);
                }
            }
        }
        if (strstr(line, "[cp2.bag]"))
        {
            printf("bag\n");
            set_character("character = \"player\"", &now_character, characters);
            snprintf(now_text, 1000, "疑?前面地上似乎有一個不知名的包包，上面甚至連個扣子都沒有");
            show(renderer, now_scene, now_character, now_text, font, &player);
            sleep(0.25);
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
                    playSound("assets/sound/sound.wav", 1000);
                    printf("playsound\n");
                    clear_events();
                    break;
                }
                // if event == B
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
                {
                    if (show_back_pack(renderer, font, player))
                    {
                        quit = true;
                        break;
                    }
                    show(renderer, now_scene, now_character, now_text, font, &player);
                    clear_events();
                }
                // if esc is pressed
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                {
                    clear_events();
                    show_image(renderer, "assets/images/esc.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                    // if esc is pressed again
                    while (1)
                    {
                        SDL_PollEvent(&event);
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            break;
                        }
                        // if e is pressed
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
                        {
                            quit = true;
                            return_type = 1;
                            break;
                        }
                        // if s is pressed
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
                        {
                            // save_system
                            // save all data
                            save(player, characters, scenes, now_scene, now_character, line, next);
                            show_image(renderer, "assets/images/black.png", 200, 200, WINDOW_WIDTH - 400, WINDOW_HEIGHT - 400);
                            show_text(renderer, "Saved", 200, 350, 150, font, (SDL_Color){255, 255, 255, 255});
                            sleep(1);
                            show_image(renderer, "assets/images/esc.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                        }
                    }
                    show(renderer, now_scene, now_character, now_text, font, &player);
                    clear_events();
                }
                if (quit)
                {
                    break;
                }
            }
            // option
            // if there are axe in the bag
            // add_item(&player, 1, "斧頭", "assets/images/axe.png", 50); for test
            option_num = 1;
            snprintf(options[0].option, 100, "嘗試使用拳頭打開");
            snprintf(options[0].next, 100, "cp2.bag_with_hand");
            for (int32_t i = 0; i < 100; i++)
            {
                if (player.back_pack[i].item_id == 1)
                {
                    option_num = 2;
                    snprintf(options[1].option, 100, "嘗試使用斧頭打開");
                    snprintf(options[1].next, 100, "cp2.bag_with_axe");
                    break;
                }
            }
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
                            snprintf(next, 1002, "[%s]", options[i].next);
                            playSound("assets/sound/click.wav", 550);
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
                // if (strstr(line, "scene ="))
                // {
                //     set_scene(line, &now_scene, scenes);
                // }
                if (strstr(line, "character ="))
                {
                    set_character(line, &now_character, characters);
                }
            }
        }
        if (strstr(line, "remove_item ="))
        {
            int32_t item_id = atoi(&line[14]);
            printf("remove item: %d\n", item_id);
            remove_item(&player, item_id);
        }
        if (strstr(line, "money_change ="))
        {
            if (line[15] == '+')
            {
                player.money += atoi(&line[16]);
            }
            else if (line[15] == '-')
            {
                player.money -= atoi(&line[16]);
            }
            else
            {
                player.money = atoi(&line[15]);
            }
        }
        bool have_mine = false;
        if (strstr(line, "[cp3.judge_mine]"))
        {
            for (int32_t i = 0; i < 100; i++)
            {
                if (player.back_pack[i].item_id == 3)
                {
                    have_mine = true;
                }
            }
            if (have_mine)
            {
                snprintf(next, 1002, "[cp3.show_mineral]");
            }
            else
            {
                snprintf(next, 1002, "[cp3.no_mineral]");
            }
            fseek(script, 0, SEEK_SET);
            while (fgets(line, sizeof(line), script))
            {
                if (strstr(line, next))
                {
                    break;
                }
            }
        }

        bool have_arrow = false;

        if (strstr(line, "[cp3.final_battle_response]"))
        {
            option_num = 1;
            snprintf(options[0].option, 100, "使用拳頭戰鬥");
            snprintf(options[0].next, 100, "cp3.fight_will_lose");
            for (int32_t i = 0; i < 100; i++)
            {
                if (player.back_pack[i].item_id == 1)
                {
                    snprintf(options[option_num].option, 100, "使用斧頭戰鬥");
                    snprintf(options[option_num].next, 100, "cp3.fight_will_win");
                    option_num++;
                }
                if (player.back_pack[i].item_id == 2)
                {
                    // find arrow
                    for (int32_t j = 0; j < 100; j++)
                    {
                        if (player.back_pack[j].item_id == 5)
                        {
                            have_arrow = true;
                            break;
                        }
                    }
                    if (have_arrow)
                    {
                        snprintf(options[option_num].option, 100, "使用弓戰鬥");
                        snprintf(options[option_num].next, 100, "cp3.fight_will_win");
                    }
                    else
                    {
                        snprintf(options[option_num].option, 100, "使用弓戰鬥(無箭矢)");
                        snprintf(options[option_num].next, 100, "cp3.fight_will_lose");
                    }
                    option_num++;
                }
                if (player.back_pack[i].item_id == 6)
                {
                    snprintf(options[option_num].option, 100, "使用開山刀戰鬥");
                    snprintf(options[option_num].next, 100, "cp3.fight_will_win");
                    option_num++;
                }
                if (player.back_pack[i].item_id == 7)
                {
                    snprintf(options[option_num].option, 100, "使用聖劍戰鬥");
                    snprintf(options[option_num].next, 100, "cp3.fight_will_win");
                    option_num++;
                }
            }
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
                            playSound("assets/sound/click.wav", 550);
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
                // if (strstr(line, "scene ="))
                // {
                //     set_scene(line, &now_scene, scenes);
                // }
                if (strstr(line, "character ="))
                {
                    set_character(line, &now_character, characters);
                }
            }
        }
        if (strstr(line, "fight ="))
        {
            if (line[8] == 1)
            {
                fight_win = true;
            }
            else
            {
                fight_win = false;
            }
        }

        if (strstr(line, "end = "))
        {
            if (line[6] == '1')
            {
                show_image(renderer, "assets/images/office.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                show_image(renderer, "assets/images/black.png", 90, 90, 500, 300);
                show_text(renderer, "結局: 拒絕接取任務", 100, 100, 50, font, (SDL_Color){255, 255, 255, 255});
                show_text(renderer, "遊戲結束", 100, 200, 50, font, (SDL_Color){255, 255, 255, 255});
                playSound("assets/sound/fail.wav", 4200);
                show_text(renderer, "按空白鍵回到主選單", 100, 300, 50, font, (SDL_Color){255, 255, 255, 255});
                // wait for space
                while (1)
                {
                    clear_events();
                    SDL_PollEvent(&event);
                    if (event.type == SDL_QUIT)
                    {
                        quit = true;
                        break;
                    }
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                    {
                        quit = true;
                        return_type = 1;
                        break;
                    }
                }
            }
            if (line[6] == '2')
            {
                show_image(renderer, "assets/images/go_die.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                show_image(renderer, "assets/images/black.png", 90, 90, 500, 300);
                show_text(renderer, "結局: 死亡", 100, 100, 50, font, (SDL_Color){255, 255, 255, 255});
                show_text(renderer, "遊戲結束", 100, 200, 50, font, (SDL_Color){255, 255, 255, 255});
                playSound("assets/sound/fail.wav", 4200);
                show_text(renderer, "按空白鍵回到主選單", 100, 300, 50, font, (SDL_Color){255, 255, 255, 255});
                // wait for space
                while (1)
                {
                    clear_events();
                    SDL_PollEvent(&event);
                    if (event.type == SDL_QUIT)
                    {
                        quit = true;
                        break;
                    }
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                    {
                        quit = true;
                        return_type = 1;
                        break;
                    }
                }
            }
            if (line[6] == '3')
            {
                show_image(renderer, "assets/images/palace.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                show_image(renderer, "assets/images/black.png", 90, 90, 500, 300);
                show_text(renderer, "結局: 完成任務", 100, 100, 50, font, (SDL_Color){255, 255, 255, 255});
                show_text(renderer, "遊戲結束", 100, 200, 50, font, (SDL_Color){255, 255, 255, 255});
                playSound("assets/sound/goodresult.wav", 3000);
                show_text(renderer, "按空白鍵回到主選單", 100, 300, 50, font, (SDL_Color){255, 255, 255, 255});
                // wait for space
                while (1)
                {
                    clear_events();
                    SDL_PollEvent(&event);
                    if (event.type == SDL_QUIT)
                    {
                        quit = true;
                        break;
                    }
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                    {
                        quit = true;
                        return_type = 1;
                        break;
                    }
                }
            }
            if (line[6] == '4')
            {
                show_image(renderer, "assets/images/palace.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                show_image(renderer, "assets/images/black.png", 90, 90, 500, 300);
                show_text(renderer, "結局: 成為守衛領隊", 100, 100, 50, font, (SDL_Color){255, 255, 255, 255});
                show_text(renderer, "遊戲結束", 100, 200, 50, font, (SDL_Color){255, 255, 255, 255});
                playSound("assets/sound/goodresult.wav", 4200);
                show_text(renderer, "按空白鍵回到主選單", 100, 300, 50, font, (SDL_Color){255, 255, 255, 255});
                // wait for space
                while (1)
                {
                    clear_events();
                    SDL_PollEvent(&event);
                    if (event.type == SDL_QUIT)
                    {
                        quit = true;
                        break;
                    }
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                    {
                        quit = true;
                        return_type = 1;
                        break;
                    }
                }
            }
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
    return return_type;
}

// int main(int argc, char const *argv[])
// {
//     char *chapter = NULL;
//     char player_name[] = "Steve";

//     // init sdl
//     SDL_Window *window = NULL;
//     SDL_Renderer *renderer = NULL;
//     int imgFlags;
//     int32_t success = initialize_window(&window, &renderer, &imgFlags);
//     TTF_Font *font = TTF_OpenFont("assets/fonts/kaiu.ttf", 24);
//     if (font == NULL)
//     {
//         printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
//     }

//     cp1(chapter, player_name, 0, renderer, font);

//     // clean up
//     TTF_CloseFont(font);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }

void show(SDL_Renderer *renderer, s_scene scene, s_character character, char *text, TTF_Font *font, s_player *player)
{
    // refresh screen
    SDL_RenderClear(renderer);
    show_image(renderer, scene.file, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    show_image(renderer, character.picture, 0, 150, 400, 600);
    show_image(renderer, "assets/images/talk_block.png", 0, 600, WINDOW_WIDTH, 300);

    // 顯示player數值
    show_image(renderer, "assets/images/black.png", 950, 300, 200, 400);
    // show player's money
    show_text(renderer, "金錢: ", 960, 320, 40, font, (SDL_Color){255, 255, 255, 255});
    char money[100];
    snprintf(money, 100, "%d", player->money);
    show_text(renderer, money, 960, 360, 40, font, (SDL_Color){255, 255, 255, 255});
    // show player's hungry
    show_text(renderer, "飽食度: ", 960, 400, 40, font, (SDL_Color){255, 255, 255, 255});
    char hungry[100];
    snprintf(hungry, 100, "%d", player->hungry);
    show_text(renderer, hungry, 960, 440, 40, font, (SDL_Color){255, 255, 255, 255});
    show_text(renderer, "按B顯示背包", 960, 480, 40, font, (SDL_Color){255, 255, 255, 255});

    // printf("%s\n", character.name_ch);
    show_text(renderer, character.name_ch, 170, 620, 50, font, (SDL_Color){255, 255, 255, 255});
    // show faverability
    if (strstr(character.name, "player") == NULL)
    {
        char favorability[100];
        snprintf(favorability, 100, "好感度: %d", character.favorability);
        show_text(renderer, favorability, 650, 670, 40, font, (SDL_Color){0, 0, 0, 255});
    }

    char text_line[256];
    int32_t text_line_num = 0;
    int32_t text_len = strlen(text);
    int32_t text_index = 0;

    while (text_len > 0)
    {
        int32_t total_bytes = 0;

        while (total_bytes + utf8_char_len(&text[text_index + total_bytes]) <= 120 && total_bytes < text_len)
        {
            total_bytes += utf8_char_len(&text[text_index + total_bytes]);
        }
        snprintf(text_line, 256, "%.*s", total_bytes, &text[text_index]);
        show_text(renderer, text_line, 20, 720 + text_line_num * 30, 36, font, (SDL_Color){0, 0, 0, 255});
        // printf("%s\n", text_line);
        text_len -= total_bytes;
        text_index += total_bytes;
        text_line_num++;
    }
    // show_text(renderer, text, 20, 730, 24, font, (SDL_Color){0, 0, 0, 255});
    show_text(renderer, "按下空白繼續", 1000, WINDOW_HEIGHT - 50, 24, font, (SDL_Color){0, 0, 0, 255});

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
        show_text(renderer, options[i].option, 50, 200 + i * 55, 50, font, (SDL_Color){255, 255, 255, 255});
    }
}

int32_t utf8_char_len(const char *s)
{
    if ((s[0] & 0x80) == 0)
        return 1; // 1-byte ASCII
    if ((s[0] & 0xE0) == 0xC0)
        return 2; // 2-byte UTF-8
    if ((s[0] & 0xF0) == 0xE0)
        return 3; // 3-byte UTF-8
    if ((s[0] & 0xF8) == 0xF0)
        return 4; // 4-byte UTF-8
    return 1;     // Default fallback (應該不會到這裡)
}

void set_faverability(char *line, s_character *characters)
{
    char character_name[20];
    char faverability[20];
    int32_t character_index = 0;
    // character.Favorability = number;
    printf("%s\n", line);
    sscanf(line, "%[^.].Favorability = %[^\r]", character_name, faverability);
    printf("%s, %s\n", character_name, faverability);

    for (int32_t i = 0; i < 10; i++)
    {
        if (strstr(character_name, characters[i].name))
        {
            printf("%s, %s\n", character_name, characters->name);
            character_index = i;
            break;
        }
    }

    printf("%d, %d->\n", character_index, characters[character_index].favorability);
    if (strstr(faverability, "+") || strstr(faverability, "-"))
    {
        if (strstr(faverability, "+"))
        {
            characters[character_index].favorability += atoi(&faverability[1]);
        }
        else
        {
            characters[character_index].favorability -= atoi(&faverability[1]);
        }
    }
    else
    {
        characters[character_index].favorability = atoi(faverability);
    }
    printf(" %d\n", characters[character_index].favorability);
    return;
}

void get_item(s_player *player, char *line, s_item *items)
{
    // get = item_id
    int32_t item_id = atoi(&line[6]);

    add_item(player, items[item_id].item_id, items[item_id].item_name, items[item_id].item_pic, items[item_id].item_health);
}

void save(s_player player, s_character *characters, s_scene *scenes, s_scene now_scene, s_character now_character, char *line, char *next)
{
    FILE *save = fopen("assets/save/save.txt", "w");
    // next
    fprintf(save, "%s\n", next);
    // player
    fprintf(save, "player.name = %s\n", player.name);
    fprintf(save, "player.money = %d\n", player.money);
    fprintf(save, "player.hungry = %d\n", player.hungry);
    for (int32_t i = 0; i < 100; i++)
    {
        if (player.back_pack[i].item_id != 0)
        {
            fprintf(save, "player.back_pack[%d].item_id = %d\n", i, player.back_pack[i].item_id);
            fprintf(save, "player.back_pack[%d].name = %s\n", i, player.back_pack[i].item_name);
            fprintf(save, "player.back_pack[%d].picture = %s\n", i, player.back_pack[i].item_pic);
            fprintf(save, "player.back_pack[%d].durability = %d\n", i, player.back_pack[i].item_health);
        }
    }
    // character
    for (int32_t i = 0; i < CHARACTER_NUM; i++)
    {
        fprintf(save, "characters[%d].name = %s\n", i, characters[i].name);
        fprintf(save, "characters[%d].name_ch = %s\n", i, characters[i].name_ch);
        fprintf(save, "characters[%d].kind = %s\n", i, characters[i].kind);
        fprintf(save, "characters[%d].picture = %s\n", i, characters[i].picture);
        fprintf(save, "characters[%d].favorability = %d\n", i, characters[i].favorability);
    }
    // scene
    fprintf(save, "now_scene = %s\n", now_scene.name);
    fprintf(save, "now_scene.name_ch = %s\n", now_scene.name_ch);
    fprintf(save, "now_scene.discription = %s\n", now_scene.discription);
    fprintf(save, "now_scene.file = %s\n", now_scene.file);
    // now_character
    fprintf(save, "now_character = %s\n", now_character.name);
    fprintf(save, "now_character.name_ch = %s\n", now_character.name_ch);
    fprintf(save, "now_character.kind = %s\n", now_character.kind);
    fprintf(save, "now_character.picture = %s\n", now_character.picture);
    fprintf(save, "now_character.favorability = %d\n", now_character.favorability);
    // line
    fprintf(save, "%s\n", line);

    fclose(save);

    return;
}

void load_data(s_player *player, s_character *characters, s_scene *scenes, s_scene *now_scene, s_character *now_character, char *line, char *next)
{
    printf("load data form last save\n");
    FILE *save = fopen("assets/save/save.txt", "r");
    char tmp[1000];
    int32_t itmp;

    // next
    fscanf(save, "%s\n", next);
    // player
    fscanf(save, "player.name = %s\n", player->name);
    // money
    fscanf(save, "player.money = %s\n", tmp);
    player->money = atoi(tmp);
    // hungry
    fscanf(save, "player.hungry = %s\n", tmp);
    player->hungry = atoi(tmp);
    // back_pack
    for (int32_t i = 0; i < 100; i++)
    {
        fscanf(save, "player.back_pack[%d].item_id = %hhd\n", &itmp, &player->back_pack[i].item_id);
        fscanf(save, "player.back_pack[%d].name = %s\n", &itmp, player->back_pack[i].item_name);
        fscanf(save, "player.back_pack[%d].picture = %s\n", &itmp, player->back_pack[i].item_pic);
        fscanf(save, "player.back_pack[%d].durability = %hhd\n", &itmp, &player->back_pack[i].item_health);
    }
    // character
    for (int32_t i = 0; i < CHARACTER_NUM; i++)
    {
        fscanf(save, "characters[%d].name = %s\n", &itmp, characters[i].name);
        fscanf(save, "characters[%d].name_ch = %s\n", &itmp, characters[i].name_ch);
        fscanf(save, "characters[%d].kind = %s\n", &itmp, characters[i].kind);
        fscanf(save, "characters[%d].picture = %s\n", &itmp, characters[i].picture);
        fscanf(save, "characters[%d].favorability = %d\n", &itmp, &characters[i].favorability);
    }
    // scene
    fscanf(save, "now_scene = %s\n", now_scene->name);
    fscanf(save, "now_scene.name_ch = %s\n", now_scene->name_ch);
    fscanf(save, "now_scene.discription = %s\n", now_scene->discription);
    fscanf(save, "now_scene.file = %s\n", now_scene->file);
    // now_character
    fscanf(save, "now_character = %s\n", now_character->name);
    fscanf(save, "now_character.name_ch = %s\n", now_character->name_ch);
    fscanf(save, "now_character.kind = %s\n", now_character->kind);
    fscanf(save, "now_character.picture = %s\n", now_character->picture);
    fscanf(save, "now_character.favorability = %d\n", &now_character->favorability);
    // line
    fscanf(save, "text = \"%[^\"]\"", line);

    fclose(save);

    return;
}

void print_data(s_player player, s_character *characters, s_scene *scenes, s_scene now_scene, s_character now_character, char *line, char *next)
{
    // printf all
    printf("next: %s\n", next);
    printf("player.name: %s\n", player.name);
    printf("player.money: %d\n", player.money);
    printf("player.hungry: %d\n", player.hungry);
    for (int32_t i = 0; i < 100; i++)
    {
        if (player.back_pack[i].item_id == 0)
        {
            continue;
        }

        printf("player.back_pack[%d].item_id: %d\n", i, player.back_pack[i].item_id);
        printf("player.back_pack[%d].name: %s\n", i, player.back_pack[i].item_name);
        printf("player.back_pack[%d].picture: %s\n", i, player.back_pack[i].item_pic);
        printf("player.back_pack[%d].durability: %d\n", i, player.back_pack[i].item_health);
    }
    for (int32_t i = 0; i < CHARACTER_NUM; i++)
    {
        printf("characters[%d].name: %s\n", i, characters[i].name);
        printf("characters[%d].name_ch: %s\n", i, characters[i].name_ch);
        printf("characters[%d].kind: %s\n", i, characters[i].kind);
        printf("characters[%d].picture: %s\n", i, characters[i].picture);
        printf("characters[%d].favorability: %d\n", i, characters[i].favorability);
    }
    printf("now_scene: %s\n", now_scene.name);
    printf("now_scene.name_ch: %s\n", now_scene.name_ch);
    printf("now_scene.discription: %s\n", now_scene.discription);
    printf("now_scene.file: %s\n", now_scene.file);
    printf("now_character: %s\n", now_character.name);
    printf("now_character.name_ch: %s\n", now_character.name_ch);
    printf("now_character.kind: %s\n", now_character.kind);
    printf("now_character.picture: %s\n", now_character.picture);
    printf("now_character.favorability: %d\n", now_character.favorability);
    printf("line: %s\n", line);

    return;
}

void init_item(s_item *item, int8_t item_id, char *item_name, char *item_pic, int8_t item_health)
{
    item->item_id = item_id;
    snprintf(item->item_name, 20, "%s", item_name);
    snprintf(item->item_pic, 100, "%s", item_pic);
    item->item_health = item_health;

    return;
}
