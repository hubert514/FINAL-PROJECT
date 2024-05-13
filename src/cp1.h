#pragma once
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

// character
#define EMPLOYER 0
#define SHADOW_BLADE 1
#define SPRIT 2
#define THIEF_LEADER 3
#define LEADER_OF_UBA 4
#define DRIVE_MAN 5
#define GUARD 6
#define EMPIRE 7

// scene
#define OFFICE 0
#define FOREST 1
#define KINGDOM_ROAD 2
#define PALACE 3

typedef struct _s_scene
{
    char name[20];
    char discription[200];
    char picture[100];
} s_scene;

int32_t cp1(char *chapter, char *player_name, int8_t player_gender);
