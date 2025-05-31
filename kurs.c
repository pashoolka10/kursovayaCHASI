#include "kurs.h"
#include <math.h>
#include <time.h>
const int width=600;
const int height=600;
const int centrX=300;
const int centrY=300;
const int rad=200;
void risovanieSTRELOK(SDL_Renderer *ren,double ugol,int dlinaStrelki,int tolshinaStrelki,SDL_Color color){// функция для рисования стрелк часов
    double radiani;
    int X2,Y2,i;
    radiani=(ugol-90)*3.14/180.0;// перевод из градусов в радианы
    X2=centrX+cos(radiani)*dlinaStrelki;// координаты стрелки
    Y2=centrY+sin(radiani)*dlinaStrelki;
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a); // установили цвет для рисования стрелок
    for (i=-tolshinaStrelki/2;i<=tolshinaStrelki/2;i++){// рисование нескольких линий для толщины стрелки
        SDL_RenderDrawLine(ren,centrX+i,centrY,X2+i,Y2);
    }
}
void risovanieTSIFR(SDL_Renderer *ren,TTF_Font *font,SDL_Color color){// функция для рисования цифр на циферблате
    char buf[3];
    double ugol;
    int i,x,y;
    for (i=1;i<=12;i++){// цикл для цифр 1-12
        ugol=(i*30-90)*3.14/180.0;//угол для размещения цифр на окружности
        x=centrX+cos(ugol)*(rad-35);//вычисление координат цифр
        y=centrY+sin(ugol)*(rad-35);
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
void otrisovkaCHASOV(SDL_Renderer *ren,TTF_Font *font,struct tm infaOVremeni,SDL_Color zadniyFon,SDL_Color peredniyFon){
    int x,y,i,r;
    double radiani,minUGOL,chasUGOL,secUGOL;
    SDL_SetRenderDrawColor(ren,zadniyFon.r,zadniyFon.g,zadniyFon.b,zadniyFon.a);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren,peredniyFon.r,peredniyFon.g,peredniyFon.b,peredniyFon.a);//отрисовка круга циферблата
    for (r=rad;r>rad-5;r--){//рисование циферблата
        for (i=0;i<360;i++){
            radiani=i*3.14/180.0;//перевод угла в радиуна
            x=centrX+cos(radiani)*r;//вычисление координат точек на окружности
            y=centrY+sin(radiani)*r;
            SDL_RenderDrawPoint(ren,x,y);
        }
    }
    risovanieTSIFR(ren, font, peredniyFon);//рисование цифр 1-12
    chasUGOL=((infaOVremeni.tm_hour % 12)+infaOVremeni.tm_min/60.0)*30;//углы поворота стрелок
    minUGOL=(infaOVremeni.tm_min+infaOVremeni.tm_sec/60.0)*6;
    secUGOL=infaOVremeni.tm_sec * 6;
    SDL_Color chasTSVET={200,0,0,255};//цвета стрелок
    SDL_Color minTSVET={0,100,200,255};
    SDL_Color secTSVET={0,200,80,255};
    risovanieSTRELOK(ren,chasUGOL,rad-90,8,chasTSVET);//отрисовка стрелок
    risovanieSTRELOK(ren,minUGOL,rad-60,5,minTSVET);
    risovanieSTRELOK(ren,secUGOL,rad-40,2,secTSVET);
    SDL_RenderPresent(ren);//отображение всего на экране
}
