#include <gif_lib.h>
#include <stdio.h>
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "show_GIF.h"

// void showError(const char *title) {
//     printf("%s: %s\n", title, SDL_GetError());
// }

int getFrameDelay(GifFileType *gif, int frameIndex) {
    for (int i = 0; i < gif->SavedImages[frameIndex].ExtensionBlockCount; i++) {
        if (gif->SavedImages[frameIndex].ExtensionBlocks[i].Function == GRAPHICS_EXT_FUNC_CODE) {
            GraphicsControlBlock gcb;
            DGifExtensionToGCB(gif->SavedImages[frameIndex].ExtensionBlocks[i].ByteCount,
                               gif->SavedImages[frameIndex].ExtensionBlocks[i].Bytes, &gcb);
            return gcb.DelayTime * 10; // DelayTime is in hundredths of a second
        }
    }
    return 100; // Default delay time if no graphics control extension is found
}

void renderGifFrame(SDL_Renderer *renderer, GifFileType *gif, int frameIndex, SDL_Surface *surface) {
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

    // Retrieve the transparent color index
    int transparentColorIndex = -1;
    for (int i = 0; i < gif->SavedImages[frameIndex].ExtensionBlockCount; i++) {
        if (gif->SavedImages[frameIndex].ExtensionBlocks[i].Function == GRAPHICS_EXT_FUNC_CODE) {
            GraphicsControlBlock gcb;
            DGifExtensionToGCB(gif->SavedImages[frameIndex].ExtensionBlocks[i].ByteCount,
                               gif->SavedImages[frameIndex].ExtensionBlocks[i].Bytes, &gcb);
            if (gcb.TransparentColor != NO_TRANSPARENT_COLOR) {
                transparentColorIndex = gcb.TransparentColor;
            }
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int offset = y * width + x;
            GifByteType colorIndex = rasterBits[offset];
            if (colorIndex != transparentColorIndex) {
                GifColorType color = colorMap[colorIndex];
                Uint32 pixelColor = SDL_MapRGB(surface->format, color.Red, color.Green, color.Blue);
                ((Uint32*)surface->pixels)[(y + top) * gif->SWidth + (x + left)] = pixelColor;
            }
        }
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        // showError("SDL_CreateTextureFromSurface Error");
        return;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}

void displayGif(SDL_Renderer *renderer, const char *gif_file) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // showError("SDL_Init Error");
        return;
    }

    // SDL_Window *win = SDL_CreateWindow("GIF Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    // if (win == NULL) {
    //     showError("SDL_CreateWindow Error");
    //     SDL_Quit();
    //     return;
    // }

    // SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // if (renderer == NULL) {
    //     showError("SDL_CreateRenderer Error");
    //     SDL_DestroyWindow(win);
    //     SDL_Quit();
    //     return;
    // }

    int error;
    GifFileType *gif = DGifOpenFileName(gif_file, &error);
    if (!gif) {
        fprintf(stderr, "DGifOpenFileName Error: %d\n", error);
        SDL_DestroyRenderer(renderer);
        // SDL_DestroyWindow(win);
        // SDL_Quit();
        return;
    }

    if (DGifSlurp(gif) != GIF_OK) {
        fprintf(stderr, "DGifSlurp Error: %d\n", gif->Error);
        DGifCloseFile(gif, &error);
        SDL_DestroyRenderer(renderer);
        // SDL_DestroyWindow(win);
        // SDL_Quit();
        return;
    }

    int quit = 0;
    SDL_Event event;
    int frame = 0;
    Uint32 last_time = 0;

    SDL_Surface *surface = SDL_CreateRGBSurface(0, gif->SWidth, gif->SHeight, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    if (!surface) {
        // showError("SDL_CreateRGBSurface Error");
        DGifCloseFile(gif, &error);
        SDL_DestroyRenderer(renderer);
        // SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        Uint32 current_time = SDL_GetTicks();
        int delay = getFrameDelay(gif, frame);
        if (current_time - last_time > delay) {
            renderGifFrame(renderer, gif, frame, surface);
            frame++;
            if (frame >= gif->ImageCount) {
                quit = 1; // Exit loop after playing all frames once
            }
            last_time = current_time;
        }

        SDL_Delay(10);
    }

    SDL_FreeSurface(surface);
    DGifCloseFile(gif, &error);
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(win);
    // SDL_Quit();
    return;
}

// int main() {
//     displayGif("assets/images/change.gif");
//     return 0;
// }