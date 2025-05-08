#include "kurs.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#define WIDTH 500
#define HEIGHT 500
#define CENTER_X (WIDTH/2)
#define CENTER_Y (HEIGHT/2)
#define RADIUS 200
void risovaneiSTRELOK(SDL_Renderer *ren,double ugol,int dlinaStrelki,int tolshinaStrelki,SDL_Color color){// функция для рисования стрелк часов
    double radiani;
    int X2,Y2,i;
    radiani=(ugol-90)*3.14/180.0;// перевод из градусов в радианы
    X2=CENTER_X+cos(radiani)*dlinaStrelki;// координаты стрелки
    Y2=CENTER_Y+sin(radiani)*dlinaStrelki;
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a); // установили цвет для рисования стрелок
    for (i=-tolshinaStrelki/2;i<=tolshinaStrelki/2;i++){// рисование нескольких линий для толщины стрелки
        SDL_RenderDrawLine(ren,CENTER_X+i,CENTER_Y+i,X2+i,Y2+i);
    }
}
void risovanieTSIFR(SDL_Renderer *ren,TTF_Font *font,SDL_Color color){// функция для рисования цифр на циферблате
    char buf[3];
    double ugol;
    int i,x,y;
    for (i=1;i<=12;i++){// цикл для цифр 1-12
        ugol=(i*30-90)*3.14/180.0;//угол для размещения цифр на окружности
        x=CENTER_X+cos(ugol)*(RADIUS-35);//вычисление координат цифр
        y=CENTER_Y+sin(ugol)*(RADIUS - 35);
        snprintf(buf,sizeof(buf),"%d",i);
        SDL_Surface *surf=TTF_RenderText_Solid(font,buf,color);// рендер текста на поверхность (текст-наши цифры)
        SDL_Texture *tex=SDL_CreateTextureFromSurface(ren,surf);//создание структуры
        int shirinaTEXTA=0,visotaTEXTA=0;
        if (surf!=NULL){// если поверхность успешно создана то получаем ширину и высоту текста
            SDL_Surface surf_copy = *surf;
            shirinaTEXTA=surf_copy.w;
            visotaTEXTA=surf_copy.h;
        }
        SDL_Rect prymougolnikDLYAcifri;// прямоугольник , в котором будет текст (цифры)
        prymougolnikDLYAcifri.x=x-shirinaTEXTA/2;
        prymougolnikDLYAcifri.y = y -visotaTEXTA/2;
        prymougolnikDLYAcifri.w = shirinaTEXTA;
        prymougolnikDLYAcifri.h = visotaTEXTA;
        SDL_RenderCopy(ren, tex, NULL, &prymougolnikDLYAcifri);
        if (surf!=NULL){
            SDL_FreeSurface(surf);
        }
        if (tex!=NULL){
            SDL_DestroyTexture(tex);
        }
    }
}
