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

// void showError(const char *title);

void renderGifFrame(SDL_Renderer *renderer, GifFileType *gif, int frameIndex, SDL_Surface *surface);

void displayGif(SDL_Renderer *renderer, const char *gif_file);

