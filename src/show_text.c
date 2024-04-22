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

int8_t show_text(SDL_Renderer *renderer, char *text, int32_t x, int32_t y, int32_t w, int32_t h, TTF_Font *font, SDL_Color color)
{
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, text, color);
    if (!textSurface)
    {
        printf("no text surface\n");
        return FALSE;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if (texture == NULL)
    {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }

    SDL_Rect dstRect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);

    return TRUE;
}