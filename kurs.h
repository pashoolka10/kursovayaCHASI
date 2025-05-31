#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdbool.h>
extern const int width;
extern const int height;
extern const int centrX;
extern const int centrY;
extern const int rad;
void risovanieSTRELOK(SDL_Renderer *ren,double ugol,int dlinaStrelki,int tolshinaStrelki,SDL_Color color);
void risovanieTSIFR(SDL_Renderer *ren,TTF_Font *font,SDL_Color color);
void otrisovkaCHASOV(SDL_Renderer *ren,TTF_Font *font,struct tm infaOVremeni,SDL_Color zadniyFon,SDL_Color peredniyFon);
