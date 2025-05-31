#include "kurs.h"
SDL_Color zadniyFon,peredniyFon;
SDL_Color zadniyFon_svetliy = {255, 255, 255, 255};
SDL_Color zadniyFon_temniy = {30, 30, 30, 255};
SDL_Color peredniyFon_svetliy = {0, 0, 0, 255};
SDL_Color peredniyFon_temniy = {255, 255, 255, 255};
int main(int argc, char *argv[]){
    bool running=true,temniy=false,zvukTIKA=true;//флаги для основного цикла (running), для темной темы (false-светлая) и для вкл/выкл звука тиканья
    int last_sec=-1;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0){
        printf("ошибка SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init()!=0){
        printf("ошибка TTF_Init: %s\n", TTF_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)!=0){
        printf("ошибка Mix_OpenAudio: %s\n", Mix_GetError());
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("Графические часы. Десятский Павел", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,height,0);
    if (win==NULL){
        printf("не удалось создать окно: %s\n", SDL_GetError());
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren==NULL){
        printf("не удалось создать renderer: %s\n",SDL_GetError());
    }
    TTF_Font *font = TTF_OpenFont("text1.ttf", 32);// загрузка шрифта
    if (font==NULL){
        printf("не найден файл шрифта text1.ttf\n");
    }
    Mix_Chunk *tick = Mix_LoadWAV("tik.wav");// загрузка звука
    if (tick==NULL){
        printf("не найден файл звука tik.wav\n");
    }
    while (running){
        SDL_Event e;
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){// закрытие окна
                running = false;
            }
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_SPACE){// переключение тем по нажатию пробела
                    temniy = !temniy;
                }
                if (e.key.keysym.sym == SDLK_s){//переключение звука по нажатию s
                    zvukTIKA = !zvukTIKA;
                    if (!zvukTIKA){
                        Mix_HaltChannel(-1);//остановка звука
                    }else{
                        Mix_PlayChannel(-1, tick, 0);//воспроизведение звука
                    }
                }
            }
        }
        time_t now = time(NULL);//получение ткущего времени
        struct tm infaOVremeni;
        localtime_r(&now,&infaOVremeni);
        if (temniy){
            zadniyFon = zadniyFon_temniy;
            peredniyFon = peredniyFon_temniy;
        }else{
            zadniyFon = zadniyFon_svetliy ;
            peredniyFon = peredniyFon_svetliy;
        }
        otrisovkaCHASOV(ren,font,infaOVremeni,zadniyFon,peredniyFon);
        if (infaOVremeni.tm_sec != last_sec){//воспроизведение тика если секунда изменилась
            last_sec = infaOVremeni.tm_sec;
            if (zvukTIKA){
                Mix_PlayChannel(-1, tick, 0);
            }
        }
        SDL_Delay(16);
    }
    Mix_FreeChunk(tick);// освобождение всех ресурсов
    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

