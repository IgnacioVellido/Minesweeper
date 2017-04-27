#include "Interfaz.h"
#include "Tablero.h"
using namespace std ;

enum Nivel {
	facil = 5 ,
	medio = 15 ,
	dificil = 30 ,
	urbano = 60 
} ;

int Menu () {
	int niv ;
	cout << "Elige un nivel\nFacil = 1\nMedio = 2\nDificil = 3\nHoli = 4" << endl ;
	cin >> niv ;
	switch (niv) {
		case 1: niv = facil ; break ;
		case 2: niv = medio ; break ;
		case 3: niv = dificil ; break ;
		case 4: niv = urbano ; break ;
		default: niv = facil ; break ;
	}
	return niv ;
}

int main( int argc, char* args[] ) {
	bool quit = false ;
	SDL_Event evento ;	

	//Start up SDL and create window
	if (!init())	cerr << "Failed to initialize!" << endl ;
	else {
		//Load media
		if (!loadMedia())	cerr << "Failed to load media!" << endl ;
		else {
			int niv = Menu() ;
//			Tablero tab(niv,8) ;
// Quitar		Base () ;
//			tab.Actualiza() ;

			while(!quit) {
				SDL_PollEvent(&evento) ;
				if (evento.type == SDL_QUIT) quit = true ;
				else if (evento.type == SDL_MOUSEBUTTONDOWN) {		
					//Get mouse position
					int x, y;
					SDL_GetMouseState(&x, &y);
					
					Transforma(x) ; Transforma(y) ;

//					if (evento.type == SDL_BUTTON_LEFT) 
//						tab.MuestraRecursivo(x,y) ;
//					else if (evento.type == SDL_BUTTON_RIGHT)
//						tab.Bandera(x,y) ; 
// Quitar					Cambia (Square_Flag, tab.matrix[x][y].casilla, Des_Transforma(x), Des_Transforma(y)) ;
//
//					if (tab.Victoria())
//					else if (tab.Derrota())

//Quitar				//Update the surface -	SI SE ACTUALIZA SE PIERDE TODO 
//Quitar				//SDL_UpdateWindowSurface(Window );

//Quitar				Des_Transforma(x) ; Des_Transforma(y) ; 
//Quitar				SDL_Rect casilla[5] ;

// Quitar				Cambia(5, x, y, casilla[5]) ;
//Quitar				Cambia(tab.matriz[x][y].valor, x, y, tab.matriz[x][y].casilla) ;
//					tab.Actualiza() ;
				}
			}
		}
	}
	//Free resources and close SDL
	close();
}
