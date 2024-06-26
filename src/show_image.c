#include <stdio.h>
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "show_image.h"

// give a pic file and x, y, w, h, and show it on the screen
int8_t show_image(SDL_Renderer *renderer, char *pic, int32_t x, int32_t y, int32_t w, int32_t h)
{
    SDL_Surface *imageSurface = IMG_Load(pic);
    SDL_Texture *texture;
    int32_t load_success = load_image(renderer, imageSurface, &texture);
    SDL_FreeSurface(imageSurface);
    if (texture == NULL)
    {
        printf("pic texture could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    

    if (load_success)
    {
        SDL_Rect dstRect = {x, y, w, h};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_RenderPresent(renderer);
    }
    else
        return false;
    SDL_DestroyTexture(texture);
    
    return load_success;
}

int32_t load_image(SDL_Renderer *renderer, SDL_Surface *imageSurface,  SDL_Texture **texture)
{
    if (imageSurface == NULL)
    {
        printf("picture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return false;
    }
    *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (texture == NULL)
    {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        return false;
    }
    return true;
}

// #include <stdio.h>
// #include "load_image.h"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include "constants.h"
// #include <stdbool.h>

// /*
//     SDL_Surface *imageSurface = IMG_Load(pic);
//     if (imageSurface == NULL)
//     {
//         printf("picture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
//         SDL_DestroyRenderer(renderer);
//         SDL_DestroyWindow(window);
//         SDL_Quit();
//         return 1;
//     }
//     SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
//     if (texture == NULL)
//     {
//         printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
//         SDL_FreeSurface(imageSurface);
//         SDL_DestroyRenderer(renderer);
//         SDL_DestroyWindow(window);
//         SDL_Quit();
//         return 1;
//     }
//     SDL_FreeSurface(imageSurface);
//     */
// int32_t load_image(SDL_Renderer *renderer, SDL_Surface *imageSurface,  SDL_Texture **texture)
// {
//     if (imageSurface == NULL)
//     {
//         printf("picture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
//         SDL_DestroyRenderer(renderer);
//         SDL_Quit();
//         return false;
//     }
//     *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
//     if (texture == NULL)
//     {
//         printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
//         SDL_FreeSurface(imageSurface);
//         return false;
//     }
//     return true;
// }
