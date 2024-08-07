#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include "show_image.h"
#include "show_text.h"
#include <unistd.h>
#include <string.h>
#include "cp1.h"
#include "set_character.h"
#include "init.h"
#include <stdbool.h>
#include "back_pack.h"
#include "playSound.h"
// #include "SDL_functions.h"

void showError(const char *title);
int8_t enter_name(SDL_Renderer *renderer, TTF_Font *font, char *playerName, int32_t nameLength);

// main function ubuntu
int main(int argc, char const *argv[])
{
    // initialize window
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int imgFlags;
    int32_t success = initialize_window(&window, &renderer, &imgFlags);
    TTF_Font *font = TTF_OpenFont("assets/fonts/NotoSansTC-Bold.ttf", 24);
    if (font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    // setup();

    // 渲染图片
    // int8_t show_success = show_image(renderer, "assets/images/sw.png", 0, 0, 500, 500);
    // show_success = show_text(renderer, "asdjiofffj 測試", 0, 600, 24, font, (SDL_Color){255, 255, 255, 255});
    SDL_Event event;
    bool quit = false;
    while (true)
    {
        quit = false;
        show_image(renderer, "assets/images/home_page.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            // if s being pressed
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
            {
                // enter name
                char playerName[21] = "";
                int nameLength = 0;

                success = enter_name(renderer, font, playerName, nameLength);
                if (success == 2)
                {
                    quit = true;
                    break;
                }

                success = cp1(0, playerName, 0, renderer, font);
                if (success == 0)
                {
                    printf("cp1 reture quit\n");
                    quit = true;
                }
                else
                {
                    show_image(renderer, "assets/images/home_page.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                    quit = false;
                }
                printf("cp1 return value: %d\n", success);
            }
            // if l being pressed
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_l)
            {
                show_image(renderer, "assets/images/black.png", 200, 200, WINDOW_WIDTH - 400, WINDOW_HEIGHT - 400);
                show_text(renderer, "Loading.", 200, 350, 150, font, (SDL_Color){255, 255, 255, 255});
                sleep(1);
                show_image(renderer, "assets/images/black.png", 200, 200, WINDOW_WIDTH - 400, WINDOW_HEIGHT - 400);
                show_text(renderer, "Loading..", 200, 350, 150, font, (SDL_Color){255, 255, 255, 255});
                sleep(1);
                show_image(renderer, "assets/images/black.png", 200, 200, WINDOW_WIDTH - 400, WINDOW_HEIGHT - 400);
                show_text(renderer, "Loading...", 200, 350, 150, font, (SDL_Color){255, 255, 255, 255});
                sleep(1);
                if (cp1(1, "player", 0, renderer, font) == 0)
                {
                    printf("cp1 reture quit\n");
                    quit = true;
                }
                else
                {
                    show_image(renderer, "assets/images/home_page.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                    quit = false;
                }
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
            {
                quit = true;
                break;
            }
            if (quit)
            {
                break;
            }
        }
        if (quit)
        {
            printf("quit\n");
            break;
        }
    }

    // clean up
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void showError(const char *title)
{
    printf("%s: %s\n", title, SDL_GetError());
}

int8_t enter_name(SDL_Renderer *renderer, TTF_Font *font, char *playerName, int32_t nameLength)
{
    SDL_Event event;
    int8_t quit = 0;
    while (SDL_PollEvent(&event))
    {
        // 仅仅读取事件，而不做任何处理
    }
    SDL_StartTextInput(); // Start text input
    playerName[0] = '\0';
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface;
    if (strlen(playerName) == 0)
    {
        show_image(renderer, "assets/images/entername.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        textSurface = TTF_RenderText_Solid(TTF_OpenFont("assets/fonts/kaiu.ttf", 50), "Enter your name:", textColor);
    }
    else
    {
        show_image(renderer, "assets/images/entername.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        textSurface = TTF_RenderText_Solid(TTF_OpenFont("assets/fonts/kaiu.ttf", 50), playerName, textColor);
    }

    if (textSurface)
    {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture)
        {
            int textWidth = textSurface->w;
            int textHeight = textSurface->h;
            SDL_FreeSurface(textSurface);

            SDL_Rect textRect = {(WINDOW_WIDTH - textWidth) / 2, (WINDOW_HEIGHT - textHeight) / 2 + 70, textWidth, textHeight};
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        else
        {
            SDL_FreeSurface(textSurface);
            showError("SDL_CreateTextureFromSurface Error");
        }
    }
    else
    {
        showError("TTF_RenderText_Solid Error");
    }
    while (!quit)
    {
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 2;
            }
            else if (event.type == SDL_TEXTINPUT)
            {
                if (nameLength < 20)
                {
                    strcat(playerName, event.text.text);
                    nameLength++;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);

                    SDL_Color textColor = {255, 255, 255, 255};
                    SDL_Surface *textSurface;
                    if (strlen(playerName) == 0)
                    {
                        show_image(renderer, "assets/images/entername.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                        textSurface = TTF_RenderText_Solid(TTF_OpenFont("assets/fonts/kaiu.ttf", 50), "Enter your name:", textColor);
                    }
                    else
                    {
                        show_image(renderer, "assets/images/entername.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                        textSurface = TTF_RenderText_Solid(TTF_OpenFont("assets/fonts/kaiu.ttf", 50), playerName, textColor);
                    }

                    if (textSurface)
                    {
                        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                        if (textTexture)
                        {
                            int textWidth = textSurface->w;
                            int textHeight = textSurface->h;
                            SDL_FreeSurface(textSurface);

                            SDL_Rect textRect = {(WINDOW_WIDTH - textWidth) / 2, (WINDOW_HEIGHT - textHeight) / 2 + 70, textWidth, textHeight};
                            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                            SDL_DestroyTexture(textTexture);
                        }
                        else
                        {
                            SDL_FreeSurface(textSurface);
                            showError("SDL_CreateTextureFromSurface Error");
                        }
                    }
                    else
                    {
                        showError("TTF_RenderText_Solid Error");
                    }

                    SDL_RenderPresent(renderer);
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_BACKSPACE && nameLength > 0)
                {
                    playerName[--nameLength] = '\0';
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);

                    SDL_Color textColor = {255, 255, 255, 255};
                    SDL_Surface *textSurface;
                    if (strlen(playerName) == 0)
                    {
                        show_image(renderer, "assets/images/entername.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                        textSurface = TTF_RenderText_Solid(TTF_OpenFont("assets/fonts/kaiu.ttf", 50), "Enter your name:", textColor);
                    }
                    else
                    {
                        show_image(renderer, "assets/images/entername.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                        textSurface = TTF_RenderText_Solid(TTF_OpenFont("assets/fonts/kaiu.ttf", 50), playerName, textColor);
                    }

                    if (textSurface)
                    {
                        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                        if (textTexture)
                        {
                            int textWidth = textSurface->w;
                            int textHeight = textSurface->h;
                            SDL_FreeSurface(textSurface);

                            SDL_Rect textRect = {(WINDOW_WIDTH - textWidth) / 2, (WINDOW_HEIGHT - textHeight) / 2 + 70, textWidth, textHeight};
                            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                            SDL_DestroyTexture(textTexture);
                        }
                        else
                        {
                            SDL_FreeSurface(textSurface);
                            showError("SDL_CreateTextureFromSurface Error");
                        }
                    }
                    else
                    {
                        showError("TTF_RenderText_Solid Error");
                    }

                    SDL_RenderPresent(renderer);
                }
                else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_RETURN2)
                {
                    quit = 1; // Exit on Enter key
                }
            }
        }
    }

    SDL_StopTextInput();

    return quit;
}