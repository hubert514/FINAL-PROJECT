#include "load_image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.h"

/*
    SDL_Surface *imageSurface = IMG_Load(pic);
    if (imageSurface == NULL)
    {
        printf("picture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (texture == NULL)
    {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_FreeSurface(imageSurface);
    */
int32_t load_image(SDL_Renderer *renderer, SDL_Surface *imageSurface,  SDL_Texture **texture)
{
    
    if (imageSurface == NULL)
    {
        printf("picture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return FALSE;
    }
    *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (texture == NULL)
    {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        return FALSE;
    }
    return TRUE;
}
