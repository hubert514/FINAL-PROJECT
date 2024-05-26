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
    //SDL_Texture* pic1 = IMG_LoadTexture(renderer, "assets/images/menu.png");
    //SDL_Texture* pic2 = IMG_LoadTexture(renderer, "assets/images/menu2.png");
    //SDL_Texture* cur_pic = pic1;
    SDL_Event event;
    int quit = 0;
    char pic1[] = "assets/images/menu.png";
    char pic2[] = "assets/images/menu2.png";
    char *cur_pic = pic1;
    while (!quit) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = 1;
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
                                show_text(renderer, "you click the botton", 0, 600, 24, font, (SDL_Color){255, 255, 255, 255});
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
            show_image(renderer, cur_pic, 0, 0, 100, 100);
            SDL_Delay(5);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    }

/*
SDL_Event event;
SDL_Texture* pic1 = IMG_LoadTexture(renderer, "pic1.png");
SDL_Texture* pic2 = IMG_LoadTexture(renderer, "pic2.png");
SDL_Texture* cur_pic = pic1;

SDL_Rect pic_rect; 
pic_rect.x = 100;  // 更換為pic1的x座標
pic_rect.y = 100;  // 更換為pic1的y座標
SDL_QueryTexture(pic1, NULL, NULL, &pic_rect.w, &pic_rect.h);  // 得到pic1的寬度和高度

while (true) {
    if (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:  // 用戶選擇退出
                SDL_DestroyTexture(pic1);
                SDL_DestroyTexture(pic2);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            case SDL_MOUSEMOTION:  // 滑鼠移動事件
                int x = event.motion.x;
                int y = event.motion.y;
                if (x >= pic_rect.x && x <= pic_rect.x + pic_rect.w && y >= pic_rect.y && y <= pic_rect.y + pic_rect.h) {
                    cur_pic = pic2; // 當滑鼠在pic1的範圍內時，切換圖片
                } else {
                    cur_pic = pic1; // 當滑鼠不在pic1的範圍內時，顯示原始圖片
                }
                break;
        }
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, cur_pic, NULL, &pic_rect);
    SDL_RenderPresent(renderer);
}*/

