#pragma once
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

// character
#define PLAYER 0
#define EMPLOYER 1
#define SHADOW_BLADE 2
#define SPRIT 3
#define THIEF_LEADER 4
#define LEADER_OF_UBA 5
#define DRIVE_MAN 6
#define GUARD 7
#define EMPIRE 8
#define OLD_MAN 9
#define CHARACTER_NUM 10

// scene
#define OFFICE 0
#define FOREST 1
#define KINGDOM_ROAD 2
#define PALACE 3
#define SCENE_NUM 4

// item
#define axe 1
#define bow 2
#define mine 3
#define walkie_talkie 4
#define arrow 5
#define machete 6
#define ex_calibur 7

typedef struct _s_scene
{
    char name_ch[20];
    char name[20];
    char discription[200];
    char file[100];
} s_scene;

typedef struct s_options
{
    char option[100];
    char next[100];
} s_options;


int32_t cp1(char *chapter, char *player_name, int8_t player_gender, SDL_Renderer *renderer, TTF_Font *font);
