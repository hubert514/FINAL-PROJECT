#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "constants.h"
#include "init.h"

int32_t initialize_window(SDL_Window **window, SDL_Renderer **renderer, int *imgFlags)
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("sdl could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // create window
    *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // create renderer
    *renderer = SDL_CreateRenderer(*window, -1, 0);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // initialize SDL_image
    *imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(*imgFlags) & *imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    // initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}
