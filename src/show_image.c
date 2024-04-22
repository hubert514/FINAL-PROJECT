#include <stdio.h>
#include "constants.h"
#include "load_image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// give a pic file and x, y, w, h, and show it on the screen
int8_t show_image(SDL_Renderer *renderer, char *pic, int32_t x, int32_t y, int32_t w, int32_t h)
{
    SDL_Surface *imageSurface = IMG_Load(pic);
    SDL_Texture *texture;
    int32_t load_success = load_image(renderer, imageSurface, &texture);
    SDL_FreeSurface(imageSurface);

    if (load_success)
    {
        SDL_Rect dstRect = {x, y, w, h};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_RenderPresent(renderer);
    }
    else
        return FALSE;
    SDL_DestroyTexture(texture);
    
    return load_success;
}