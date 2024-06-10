#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main(int argc,char* argv[]){
    SDL_Init(SDL_INIT_AUDIO);   // 初始化 SDL 音訊系統

    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return 0;
    } 

    Mix_Chunk *gScratch = NULL; // 載入 wav 音效檔
    gScratch = Mix_LoadWAV("assets/images/sound.wav");
    if(gScratch == NULL) { 
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return 0; 
    }

    Mix_PlayChannel( -1, gScratch, 0 ); // 播放音效檔
    SDL_Delay(5000); // 等待 5000 毫秒
    Mix_FreeChunk(gScratch); // 釋放音效檔資源
    Mix_CloseAudio(); // 退出 SDL
    SDL_Quit();
    return 0;
}