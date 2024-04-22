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

// give a pic file and x, y, w, h, and show it on the screen
int8_t show_image(SDL_Renderer *renderer, char *pic, int32_t x, int32_t y, int32_t w, int32_t h);
