#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
// Para png #include <SDL_image.h>


using namespace std ;

//Screen dimension constants
const int SCREEN_WIDTH = 144;
const int SCREEN_HEIGHT = 144;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

enum Squares {
	Square_0
	Square_1
	Square_2
	Square_3
	Square_4
	Square_5
	Square_6
	Square_7
	Square_8
	Square_Bomb
	Square_Flag
	Square_Border
}

bool init () ;
bool loadMedia() ;
void close () ;

	// Inicializar pantalla - Cargar imágenes
	// Despliga menu
	// Pide nivel - Construye Tablero
	
int main( int argc, char* args[] )
{
	bool quit = false ;
	
	SDL_Event evento ;	

	//Start up SDL and create window
	if ( !init() )	cerr << "Failed to initialize!" << endl ;
	else
	{
		//Load media
		if ( !loadMedia() )	cerr << "Failed to load media!" << endl ;
		else
		{
			while(!quit) {
				SDL_PollEvent(&evento) ;
				if (evento.type == SDL_QUIT) quit = true ;
				else {	
					//Apply the image
					SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
				
					//Update the surface
					SDL_UpdateWindowSurface( gWindow );
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cerr << "SDL could not initialize! SDL_Error:\n" << SDL_GetError() << endl ;
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Probando a cargar imagen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			cerr << "Window could not be created! SDL_Error:\n" << SDL_GetError() << endl ;
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}


bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP( "files/minesweeper.bmp" );
	if( gHelloWorld == NULL )
	{
		cerr << "Unable to load image! files/minesweeper.bmp" << SDL_GetError() << endl ;
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

/*/////////// VER PARA QUE SIRVE /////////////////////////

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	gSquaresSurfaces[Square_0] = loadSurface( "files/0.png

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprites
	if( !gButtonSpriteSheetTexture.loadFromFile( "17_mouse_events/button.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else
	{
		//Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = 0;
			gSpriteClips[ i ].y = i * 200;
			gSpriteClips[ i ].w = BUTTON_WIDTH;
			gSpriteClips[ i ].h = BUTTON_HEIGHT;
		}

		//Set buttons in corners
		gButtons[ 0 ].setPosition( 0, 0 );
		gButtons[ 1 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
		gButtons[ 2 ].setPosition( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
		gButtons[ 3 ].setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );
	}

	return success;
}

*/
