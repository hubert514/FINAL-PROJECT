#include <stdio.h>
#include <stdint.h>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL.h"
#include "constants.h"
#include <unistd.h>
#include "load_image.h"
// #include "SDL_functions.h"

// set up the window
int32_t initialize_window(void);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int imgFlags;

// main function ubuntu
int main(int argc, char const *argv[])
{
    // initialize window
    int32_t success = initialize_window();

    // setup();

    SDL_Surface *imageSurface = IMG_Load("assets/images/sw.png"), *imageSurface_a = IMG_Load("assets/images/sss.png");
    SDL_Texture *texture_1, *texture_2;
    int32_t load_success;

    if (load_success = load_image(renderer, imageSurface, &texture_1))
    {
        printf("load success\n");
    }

    if (load_success = load_image(renderer, imageSurface_a, &texture_2))
    {
        printf("load success\n");
    }

    // 指定图片位置
    int32_t img_sw_w = imageSurface->w * WINDOW_HEIGHT / imageSurface->h;

    SDL_Rect dstRect = {0, 0, img_sw_w, WINDOW_HEIGHT}, dstRect_2 = {200, 200, img_sw_w, WINDOW_HEIGHT};

    // 渲染图片
    SDL_RenderCopy(renderer, texture_1, NULL, &dstRect);
    SDL_RenderPresent(renderer);

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
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture_2, NULL, &dstRect);
                SDL_RenderPresent(renderer);
            }
        }
        if (event.type == SDL_QUIT)
        {
            break;
        }
    }

    // clean up
    SDL_DestroyTexture(texture_1);
    SDL_DestroyTexture(texture_2);
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(imageSurface_a);

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
    return TRUE;
}
