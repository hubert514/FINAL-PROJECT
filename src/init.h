#pragma once
#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int32_t initialize_window(SDL_Window **window, SDL_Renderer **renderer, int *imgFlags);
