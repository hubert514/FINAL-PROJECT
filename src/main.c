#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include <unistd.h>
// #include "SDL_functions.h"

// set up the window
int32_t initialize_window(void);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// main function ubuntu
int main(int argc, char const *argv[])
{
    // initialize window
    int32_t success = initialize_window();

    //setup();
    while (success)
    {
        sleep(3);
        break;
    }
    


    // destroy window
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

    return TRUE;
}
