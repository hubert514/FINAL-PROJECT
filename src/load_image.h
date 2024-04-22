#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// char pic[100] = "assets/images/sw.png";
// SDL_Surface *imageSurface = IMG_Load(pic);
// SDL_Texture *texture;
// int32_t load_success = load_image(renderer, imageSurface, &texture);
// SDL_FreeSurface(imageSurface);
int32_t load_image(SDL_Renderer *renderer, SDL_Surface *imageSurface, SDL_Texture **texture);