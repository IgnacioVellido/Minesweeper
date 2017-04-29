#include "Tablero.h"
#include <iostream>
using namespace std ;

SDL_Window* Window = NULL ;
SDL_Surface* Surface = NULL ;
SDL_Texture* Images[Square_Total] = {NULL} ;
SDL_Renderer* Renderer = NULL ;

//Screen dimension constants 8x8
const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 160;
const int BUTTON_WIDTH_HEIGHT = 20;

SDL_Texture* loadTexture (std::string path) ;
bool loadMedia () ;
inline void Transforma (int &pos) { pos /= BUTTON_WIDTH_HEIGHT ; }
//Quitar inline void Des_Transforma (int &pos) { pos *= BUTTON_WIDTH_HEIGHT ; }
bool init () ;
void close () ;
void Actualiza (Tablero &tab) ;

enum Nivel {
	facil = 5 ,
	medio = 15 ,
	dificil = 30 ,
	urbano = 60 
} ;

// Arreglar, hacer con imágenes
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
//			int niv = Menu() ;
			Tablero tab(5,8) ;
			Actualiza(tab) ;

			while(!quit) {
				SDL_PollEvent(&evento) ;
				if (evento.type == SDL_QUIT) quit = true ;
				else if (evento.type == SDL_MOUSEBUTTONDOWN) {		
					//Get mouse position
					int x, y;
					SDL_GetMouseState(&x, &y);
			
					Transforma(x) ; Transforma(y) ; 

					if (evento.button.button == SDL_BUTTON_LEFT)
						tab.MuestraRecursivo(x,y) ; 
					else if (evento.button.button == SDL_BUTTON_RIGHT)
						tab.Bandera(x,y) ;

//					if (tab.Victoria())
//					else if (tab.Derrota())

//Quitar				Des_Transforma(x) ; Des_Transforma(y) ; 
					Actualiza(tab) ;  
				}
			}
		}
	}
	//Free resources and close SDL
	close();
}

SDL_Texture* loadTexture (std::string path) {
	SDL_Texture* newTexture = NULL ;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str()) ;
	if (loadedSurface == NULL) cerr << "No se pudo cargar la imagen: " << path.c_str() << IMG_GetError() << endl ;
	else {
		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface) ;
		if(newTexture == NULL) cerr << "No se pudo crear la textura de: " << path.c_str() << SDL_GetError() << endl ;
		SDL_FreeSurface (loadedSurface) ;
	}
	return newTexture ;
}

bool loadMedia() {
	bool success = true ;
	Images[Square_0] = loadTexture( "files/0.png" ); 
		if( Images[Square_0] == NULL )
		{
			cerr << "Unable to load image! files/0.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_1] = loadTexture( "files/1.png" );
		if( Images[Square_1] == NULL )
		{
			cerr << "Unable to load image! files/1.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_2] = loadTexture( "files/2.png" );
		if( Images[Square_2] == NULL )
		{
			cerr << "Unable to load image! files/2.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_3] = loadTexture( "files/3.png" );
		if( Images[Square_3] == NULL )
		{
			cerr << "Unable to load image! files/3.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_4] = loadTexture( "files/4.png" );
		if( Images[Square_4] == NULL )
		{
			cerr << "Unable to load image! files/4.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_5] = loadTexture( "files/5.png" );
		if( Images[Square_5] == NULL )
		{
			cerr << "Unable to load image! files/5.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_6] = loadTexture( "files/6.png" );
		if( Images[Square_6] == NULL )
		{
			cerr << "Unable to load image! files/6.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_7] = loadTexture( "files/7.png" );
		if( Images[Square_7] == NULL )
		{
			cerr << "Unable to load image! files/7.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_8] = loadTexture( "files/8.png" );
		if( Images[Square_8] == NULL )
		{
			cerr << "Unable to load image! files/8.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_Bomb] = loadTexture( "files/bomb.png" );
		if( Images[Square_Bomb] == NULL )
		{
			cerr << "Unable to load image! files/bomb.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_Boom] = loadTexture( "files/boom.png" );
		if( Images[Square_Boom] == NULL )
		{
			cerr << "Unable to load image! files/boom.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_Flag] = loadTexture( "files/flag.png" );
		if( Images[Square_Flag] == NULL )
		{
			cerr << "Unable to load image! files/flag.png " << SDL_GetError() << endl ; success = false;
		}
	Images[Square_Hide] = loadTexture( "files/hide.png" );
		if( Images[Square_Hide] == NULL )
		{
			cerr << "Unable to load image! files/hide.png " << SDL_GetError() << endl ; success = false;
		}

	return success;
}

bool init() {
	bool success = true;

	//Initialize SDL
	if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
		cerr << "SDL could not initialize! SDL_Error:\n" << SDL_GetError() << endl ; success = false;
	}
	else {
		//Create window
		Window = SDL_CreateWindow("Buscaminas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(Window == NULL) {
			cerr << "Window could not be created! SDL_Error:\n" << SDL_GetError() << endl ; success = false;
		}
		else {
			Renderer = SDL_CreateRenderer (Window, -1, SDL_RENDERER_ACCELERATED) ;
			if (Renderer == NULL) {
				cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl ; success = false ;
			}
			else {		
				 SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				
				//Initialize PNG loading 
				int imgFlags = IMG_INIT_PNG; 
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) { 
					cerr << "SDL_image could not be created! SDL_Error:\n" << IMG_GetError() << endl ; success = false; 					} 
				else
					//Get window surface
					Surface = SDL_GetWindowSurface(Window); 
			}
		}
	}
	return success;
}

void close() {
	//Free loaded images
	for (int i = 0 ; i < Square_Total ; i++) SDL_DestroyTexture(Images[i]) ;
//	Images = {NULL} ;
	
	// Destroy window
	SDL_DestroyRenderer(Renderer) ;
	SDL_DestroyWindow(Window) ;
	Window = NULL ; Renderer = NULL ;

	// Quit SDL subsystems
	IMG_Quit() ;
	SDL_Quit() ;
}

void Actualiza (Tablero &tab) {
	for (int i = 0 ; i < tab.GetTamanio() ; i ++) {
		for (int j = 0 ; j < tab.GetTamanio() ; j ++) {
			tab.matriz[i][j].casilla.x = i*BUTTON_WIDTH_HEIGHT ; tab.matriz[i][j].casilla.y = j*BUTTON_WIDTH_HEIGHT ;
			tab.matriz[i][j].casilla.w = tab.matriz[i][j].casilla.h = BUTTON_WIDTH_HEIGHT ;
			SDL_RenderSetViewport (Renderer, &tab.matriz[i][j].casilla) ;
			if (tab.matriz[i][j].bandera == true)
				SDL_RenderCopy(Renderer,Images[Square_Flag], NULL, NULL) ;
			else if (tab.matriz[i][j].valor == Square_Bomb)
				SDL_RenderCopy(Renderer,Images[Square_Hide], NULL, NULL) ;
			else 
				SDL_RenderCopy(Renderer,Images[tab.matriz[i][j].valor], NULL, NULL) ;				
		}
	}
	SDL_RenderPresent(Renderer) ;
}
