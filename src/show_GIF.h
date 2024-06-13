#pragma once
#include <stdio.h>
#include <stdint.h> 
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include <gif_lib.h>
#include "show_image.h"
#include "show_text.h"
#include <unistd.h>

void showError(const char *title);

void renderGifFrame(SDL_Renderer *renderer, GifFileType *gif, int frameIndex, SDL_Surface *surface);

int8_t show_GIF(SDL_Renderer *renderer, char *gif, int32_t x, int32_t y, int32_t w, int32_t h);

