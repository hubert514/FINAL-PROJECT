#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "playSound.h"

int playSound(const char *soundFile,int time) {
    // 初始化 SDL 音訊系統
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 初始化 SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    // 載入 wav 音效檔
    Mix_Chunk *sound = Mix_LoadWAV(soundFile);
    if (sound == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    // 播放音效
    Mix_PlayChannel(-1, sound, 0);

    // 等待然後釋放資源
    SDL_Delay(time);
    Mix_FreeChunk(sound);

    // 關閉 SDL_mixer 和 SDL
    Mix_CloseAudio();

    return 0;
}

/*int main() {
    playSound("assets/sound.wav");
    return 0;
}*/