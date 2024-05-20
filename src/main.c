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
#include "init.h"
#include <stdbool.h>
// #include "SDL_functions.h"

// main function ubuntu
int main(int argc, char const *argv[])
{
    // initialize window
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int imgFlags;
    char font[100] = "assets/fonts/kaiu.ttf";
    int32_t success = initialize_window(&window, &renderer, &imgFlags);
    if (!TTF_OpenFont(font, 24))
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    // setup();

    // 渲染图片
    int8_t show_success = show_image(renderer, "assets/images/sw.png", 0, 0, 500, 500);
    show_success = show_text(renderer, "hello world", 0, 600, strlen("hello world") * 24 / 2, 24, TTF_OpenFont(font, 24), (SDL_Color){255, 255, 255, 255});
    SDL_Event event;

    while (true)
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
