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
// #include "SDL_functions.h"

// set up the window
int32_t initialize_window(void);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int imgFlags;
char font[100] = "assets/fonts/kaiu.ttf";

// main function ubuntu
int main(int argc, char const *argv[])
{
    // initialize window
    int32_t success = initialize_window();
    if (!TTF_OpenFont(font, 24))
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    // setup();

    // 渲染图片
    int8_t show_success = show_image(renderer, "assets/images/sw.png", 0, 0, 500, 500);
    show_success = show_text(renderer, "hello world", 0, 600, strlen("hello world") * 24 / 2, 24, TTF_OpenFont(font, 24), (SDL_Color){255, 255, 255, 255});
    SDL_Event event;

    while (TRUE)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                show_image(renderer, "assets/images/sss.png", 0, 0, 500, 500);
            }
        }
        if (event.type == SDL_QUIT)
        {
            break;
        }
    }

    // clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// set up the window
int32_t initialize_window(void)
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("sdl could not initialize! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }

    // create window
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }

    // create renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }

    // initialize SDL_image
    imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return FALSE;
    }

    // initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return FALSE;
    }

    return TRUE;
}
