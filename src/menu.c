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
#include "init.h"
#include <stdbool.h>
#include "constants.h"

int main(int argc, char const *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int imgFlags;
    initialize_window(&window, &renderer, &imgFlags);
    SDL_Color color;
    TTF_Font *font = TTF_OpenFont("assets/fonts/kaiu.ttf", 24);
    if(font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    SDL_Event event;
    int quit = 0;
    char pic1[] = "assets/images/menu.png";
    char pic2[] = "assets/images/menu2.png";
    char *cur_pic = pic1;
    int mouse_press = 0;
    int quita = 0;
    int main_menu = 1;
    while(main_menu == 1){
        while (!quit) {
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_QUIT:
                            quit = 1;
                            main_menu = 0;
                            break;
                        case SDL_MOUSEMOTION:
                            if (event.motion.x >= 0 && event.motion.x <= 100 && event.motion.y >= 0 && event.motion.y <= 100) {
                                cur_pic = pic2;
                            } else {
                                cur_pic = pic1;
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event.button.button == SDL_BUTTON_LEFT) {
                                if (event.button.x >= 0 && event.button.x <= 100 && event.button.y >= 0 && event.button.y <= 100) {
                                    mouse_press = 1;
                                    SDL_RenderClear(renderer);
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
                show_image(renderer, cur_pic, 0, 0, 100, 100);
                SDL_Delay(5);
                if(mouse_press == 1) {
                    show_image(renderer, "assets/images/back.png", WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 275, 200, 100);
                    show_image(renderer, "assets/images/exit.png", WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 50, 200, 100);
                    show_image(renderer, "assets/images/save.png", WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 175, 200, 100);
                    quita = 0;
                    while( !quita ) {
                        while (SDL_PollEvent(&event)) {
                            switch (event.type) {
                                case SDL_QUIT:
                                    quit = 1;
                                    quita = 1;
                                    main_menu = 0;
                                    break;
                                case SDL_MOUSEBUTTONDOWN:
                                    if (event.button.button == SDL_BUTTON_LEFT) {
                                        if (event.button.x >= WINDOW_WIDTH/2 - 100 && event.button.x <= WINDOW_WIDTH/2 + 100 && event.button.y >= WINDOW_HEIGHT/2 - 50 && event.button.y <= WINDOW_HEIGHT/2 + 50) {
                                            printf("Exit\n");
                                            mouse_press = 0;
                                            quita = 1;
                                            quit = 1;
                                            main_menu = 0;
                                            SDL_RenderClear(renderer);
                                        }
                                        else if (event.button.x >= WINDOW_WIDTH/2 - 100 && event.button.x <= WINDOW_WIDTH/2 + 100 && event.button.y >= WINDOW_HEIGHT/2 - 275 && event.button.y <= WINDOW_HEIGHT/2 - 175) {
                                            printf("Back\n");
                                            mouse_press = 0;
                                            quita = 1;
                                            SDL_RenderClear(renderer);
                                            break;
                                        }
                                        else if (event.button.x >= WINDOW_WIDTH/2 - 100 && event.button.x <= WINDOW_WIDTH/2 + 100 && event.button.y >= WINDOW_HEIGHT/2 + 175 && event.button.y <= WINDOW_HEIGHT/2 + 275) {
                                            printf("Save\n");
                                            SDL_RenderClear(renderer);
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;
                    }  
                }
        }
    }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    }


