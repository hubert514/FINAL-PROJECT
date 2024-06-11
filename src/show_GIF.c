#include <stdio.h>
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <gif_lib.h>


void showError(const char *title) {
    printf("%s: %s\n", title, SDL_GetError());
}

void renderGifFrame(SDL_Renderer *renderer, GifFileType *gif, int frameIndex, SDL_Surface **prevSurface) {
    GifColorType *colorMap;
    GifImageDesc *imgDesc = &gif->SavedImages[frameIndex].ImageDesc;
    if (imgDesc->ColorMap) {
        colorMap = imgDesc->ColorMap->Colors;
    } else {
        colorMap = gif->SColorMap->Colors;
    }

    int top = imgDesc->Top;
    int left = imgDesc->Left;
    int width = imgDesc->Width;
    int height = imgDesc->Height;
    GifByteType *rasterBits = gif->SavedImages[frameIndex].RasterBits;

    SDL_Surface *surface;
    if (*prevSurface) {
        surface = *prevSurface;
    } else {
        surface = SDL_CreateRGBSurface(0, gif->SWidth, gif->SHeight, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        *prevSurface = surface;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int offset = y * width + x;
            GifColorType color = colorMap[rasterBits[offset]];
            Uint32 pixelColor = SDL_MapRGB(surface->format, color.Red, color.Green, color.Blue);
            ((Uint32*)surface->pixels)[(y + top) * gif->SWidth + (x + left)] = pixelColor;
        }
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        showError("SDL_CreateTextureFromSurface Error");
        return;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}

int main(int argc, char *argv[]) {
    const char *gif_file = "/mnt/c/Users/user/Desktop/homework/FINAL-PROJECT/assets/images/gif.gif";

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        showError("SDL_Init Error");
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("GIF Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        showError("SDL_CreateWindow Error");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        showError("SDL_CreateRenderer Error");
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    int error;
    GifFileType *gif = DGifOpenFileName(gif_file, &error);
    if (!gif) {
        fprintf(stderr, "DGifOpenFileName Error: %d\n", error);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    if (DGifSlurp(gif) != GIF_OK) {
        fprintf(stderr, "DGifSlurp Error: %d\n", gif->Error);
        DGifCloseFile(gif, &error);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    int quit = 0;
    SDL_Event event;
    int frame = 0;
    Uint32 last_time = 0;
    SDL_Surface *prevSurface = NULL;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        Uint32 current_time = SDL_GetTicks();
        if (current_time - last_time > 100) { // 100 ms per frame
            frame = (frame + 1) % gif->ImageCount;
            renderGifFrame(renderer, gif, frame, &prevSurface);
            last_time = current_time;
        }

        SDL_Delay(10);
    }

    if (prevSurface)
        SDL_FreeSurface(prevSurface);

    DGifCloseFile(gif, &error);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}