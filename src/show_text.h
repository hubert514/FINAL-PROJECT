#include <stdio.h>
#include <stdint.h> 
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include "load_image.h"
#include "show_image.h"
#include <unistd.h>

// show text on the screen
int8_t show_text(SDL_Renderer *renderer, char *text, int32_t x, int32_t y, int32_t w, int32_t h, TTF_Font *font, SDL_Color color);
