#include <stdio.h>
#include <stdint.h> 
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include "show_image.h"
#include "show_text.h"
#include <unistd.h>
#include <stdbool.h>

int8_t show_text(SDL_Renderer *renderer, char *text, int32_t x, int32_t y, int32_t font_size, TTF_Font *font, SDL_Color color)
{
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, text, color);
    if (!textSurface)
    {
        printf("no text surface\n");
        return false;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if (texture == NULL)
    {
        printf("text texture could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Rect dstRect = {x, y, strlen(text) * font_size / 1.9, font_size};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);

    return true;
}