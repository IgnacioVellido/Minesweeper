#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std ;

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

//Screen dimension constants 8x8
const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 160;
const int BUTTON_WIDTH_HEIGHT = 20;

SDL_Window* Window = NULL ;
SDL_Surface* Surface = NULL ;
SDL_Texture* Images[Square_Total] = {NULL} ;
SDL_Renderer* Renderer = NULL ;

SDL_Texture* loadTexture (std::string path) ;
bool loadMedia () ;
inline void Transforma (int &pos) { pos /= BUTTON_WIDTH_HEIGHT ; }
inline void Des_Transforma (int &pos) { pos *= BUTTON_WIDTH_HEIGHT ; }
bool init () ;
void close () ;
void Base () ;
//////////////////////////////////////////////////////////////////
// Esto superpone imágenes - CAMBIAR
void Cambia (int img, int x, int y) {
	SDL_Rect Viewport ; 

	Viewport.x = x ; Viewport.y = y ;
	Viewport.w = Viewport.h = BUTTON_WIDTH_HEIGHT ;
	SDL_RenderSetViewport (Renderer, &Viewport) ;
	SDL_RenderCopy(Renderer,Images[Square_1], NULL, NULL) ;

	SDL_RenderPresent(Renderer) ;
}
//////////////////////////////////////////////////////////////////

int main( int argc, char* args[] ) {
	bool quit = false ;
	SDL_Event evento ;	

	//Start up SDL and create window
	if (!init())	cerr << "Failed to initialize!" << endl ;
	else {
		//Load media
		if (!loadMedia())	cerr << "Failed to load media!" << endl ;
		else {
			Base () ;
			while(!quit) {
				SDL_PollEvent(&evento) ;
				if (evento.type == SDL_QUIT) quit = true ;
				else if (evento.type == SDL_MOUSEBUTTONDOWN) {		
					//Get mouse position
					int x, y;
					SDL_GetMouseState(&x, &y);
					
					Transforma(x) ; Transforma(y) ;
					cout << x << " " << y << endl ;

					//Update the surface -	SI SE ACTUALIZA SE PIERDE TODO 
					//SDL_UpdateWindowSurface(Window );

					Des_Transforma(x) ; Des_Transforma(y) ; 
					Cambia(Square_1, x, y) ;
				}
			}
		}
	}
	//Free resources and close SDL
	close();
}



//////////////////////////////////////////////////////////////////////////////////////////

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

void Base () {
	SDL_RenderClear(Renderer) ;
	SDL_Rect Viewport; 
	for (int i = 0 ; i <= SCREEN_WIDTH ; i += BUTTON_WIDTH_HEIGHT) {
		for (int j = 0 ; j <= SCREEN_WIDTH ; j += BUTTON_WIDTH_HEIGHT) {
			Viewport.x = i ; Viewport.y = j ;
			Viewport.w = Viewport.h = BUTTON_WIDTH_HEIGHT ;
			SDL_RenderSetViewport (Renderer, &Viewport) ;
			SDL_RenderCopy(Renderer,Images[Square_0], NULL, NULL) ;
		}
	}
	SDL_RenderPresent(Renderer) ;
}
