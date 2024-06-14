// #include <stdio.h>
// #include "constants.h"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <string.h>
// #include "SDL2/SDL_ttf.h"
// #include "show_image.h"


// #define MAX_NAME_LENGTH 20

// void showError(const char *title) {
//     printf("%s: %s\n", title, SDL_GetError());
// }

// int main(int argc, char *argv[]) {
//     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//         showError("SDL_Init Error");
//         return 1;
//     }

//     if (TTF_Init() != 0) {
//         showError("TTF_Init Error");
//         SDL_Quit();
//         return 1;
//     }

//     SDL_Window *win = SDL_CreateWindow("Enter Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
//     if (win == NULL) {
//         showError("SDL_CreateWindow Error");
//         TTF_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     if (renderer == NULL) {
//         showError("SDL_CreateRenderer Error");
//         SDL_DestroyWindow(win);
//         TTF_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     TTF_Font *font = TTF_OpenFont("assets/fonts/kaiu.ttf", 45); // Use a valid path to a .ttf file
//     if (!font) {
//         showError("TTF_OpenFont Error");
//         SDL_DestroyRenderer(renderer);
//         SDL_DestroyWindow(win);
//         TTF_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     int quit = 0;
//     SDL_Event event;
//     char playerName[MAX_NAME_LENGTH + 1] = "";
//     int nameLength = 0;

//     SDL_StartTextInput(); // Start text input

//     while (!quit) {
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 quit = 1;
//             } else if (event.type == SDL_TEXTINPUT) {
//                 if (nameLength < MAX_NAME_LENGTH) {
//                     strcat(playerName, event.text.text);
//                     nameLength++;
//                 }
//             } else if (event.type == SDL_KEYDOWN) {
//                 if (event.key.keysym.sym == SDLK_BACKSPACE && nameLength > 0) {
//                     playerName[--nameLength] = '\0';
//                 } else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_RETURN2) {
//                     quit = 1; // Exit on Enter key
//                 }
//             }
//         }

//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);

//         SDL_Color textColor = { 255, 255, 255, 255 };
//         SDL_Surface *textSurface;
//         if (strlen(playerName) == 0) {
//             show_image(renderer, "assets/images/entername.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
//             textSurface = TTF_RenderText_Solid(font, "Enter your name:", textColor);
//         } else {
//             show_image(renderer, "assets/images/entername.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
//             textSurface = TTF_RenderText_Solid(font, playerName, textColor);
//         }

//         if (textSurface) {
//             SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//             if (textTexture) {
//                 int textWidth = textSurface->w;
//                 int textHeight = textSurface->h;
//                 SDL_FreeSurface(textSurface);

//                 SDL_Rect textRect = { (WINDOW_WIDTH - textWidth) / 2, (WINDOW_HEIGHT - textHeight) / 2+70, textWidth, textHeight };
//                 SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
//                 SDL_DestroyTexture(textTexture);
//             } else {
//                 SDL_FreeSurface(textSurface);
//                 showError("SDL_CreateTextureFromSurface Error");
//             }
//         } else {
//             showError("TTF_RenderText_Solid Error");
//         }

//         SDL_RenderPresent(renderer);
//     }

//     SDL_StopTextInput(); // Stop text input

//     TTF_CloseFont(font);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(win);
//     TTF_Quit();
//     SDL_Quit();

//     printf("Player Name: %s\n", playerName);

//     return 0;
// }