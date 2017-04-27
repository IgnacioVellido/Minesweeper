#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

enum Squares {
	Square_0,
	Square_1,
	Square_2,
	Square_3,
	Square_4,
	Square_5,
	Square_6,
	Square_7,
	Square_8,
	Square_Bomb,
	Square_Boom,
	Square_Flag,
	Square_Hide,
	Square_Total
} ;

SDL_Window* Window = NULL ;
SDL_Surface* Surface = NULL ;
SDL_Texture* Images[Square_Total] = {NULL} ;
SDL_Renderer* Renderer = NULL ;

//Screen dimension constants 8x8
const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 160;
const int BUTTON_WIDTH_HEIGHT = 20;

////Quitar	void Cambia (int, SDL_Rect, int, int) ;
SDL_Texture* loadTexture (std::string path) ;
bool loadMedia () ;
inline void Transforma (int &pos) { pos /= BUTTON_WIDTH_HEIGHT ; }
//Quitar inline void Des_Transforma (int &pos) { pos *= BUTTON_WIDTH_HEIGHT ; }
bool init () ;
void close () ;
//Quitar void Base () ;

#endif
