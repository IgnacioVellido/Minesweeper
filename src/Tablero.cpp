#include "Tablero.h"

void Tablero::Actualiza () {
//	SDL_RenderClear(Renderer) ;
//	SDL_Rect Viewport; 
	for (int i = 0 ; i < tamanio ; i ++) {
		for (int j = 0 ; j < tamanio ; j ++) {
			matriz[i][j].casilla.x = i*BUTTON_WIDTH_HEIGHT ; matriz[i][j].casilla.y = j*BUTTON_WIDTH_HEIGHT ;
			matriz[i][j].casilla.w = matriz[i][j].casilla.h = BUTTON_WIDTH_HEIGHT ;
			SDL_RenderSetViewport (Renderer, &matriz[i][j].casilla) ;
			if (matriz[i][j].bandera == false)
				SDL_RenderCopy(Renderer,Images[matriz[i][j].valor], NULL, NULL) ;
			else 
				SDL_RenderCopy(Renderer,Images[Square_Flag], NULL, NULL) ;
		}
	}
	SDL_RenderPresent(Renderer) ;
}


int Tablero::GeneraAleatorio (){
	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> dis(0, tamanio-1); 
	return (dis(gen)) ;
}

	// Añade bombas en posiciones aleatorias hasta un maximo definido por el nivel  - FUNCIONA
void Tablero::InsertBomb () {
	int fila , colum ,
	    contador = 0 ;

	while (contador != nivel) {
		fila = GeneraAleatorio() ;
		colum = GeneraAleatorio() ;
		// Se podria acceder con punteros (?) 
		if (matriz[fila][colum].valor != Square_Bomb) { 
			matriz[fila][colum].valor = Square_Bomb ; contador++ ;
		} 
	}
}

	// Precondición: No es bomba
void Tablero::CalculaValor (int fila, int colum) {
	bool accesible ;
	for (int i = fila - 1 ; i <= fila+1 ; i++) { 
		for (int j = colum - 1 ; j <= colum+1 ; j++) 	{ 
			accesible = (i >= 0 && i < tamanio) && (j >= 0 && j < tamanio) ;
			if (accesible && fila != colum) {
				if (matriz[i][j].valor == Square_Bomb)
					matriz[fila][colum].valor++ ;
			}
		}
	}
}

void Tablero::MuestraRecursivo (int fila , int colum) {
	bool accesible = (fila >= 0 && fila < tamanio) && (colum >= 0 && colum < tamanio) ;
	if (accesible) {
		if (matriz[fila][colum].bandera == false && matriz[fila][colum].mostrada == false ) {
			if (matriz[fila][colum].valor != Square_Bomb) {
				
				CalculaValor(fila,colum) ;

				// Mostrar posicion - Llamar a una función que lo haga y que incluya:
				matriz[fila][colum].mostrada = true ;

				// En el original, si es un número no muestra más
				if (matriz[fila][colum].valor == 0) {
					MuestraRecursivo(fila-1,colum) ;
					MuestraRecursivo(fila+1,colum) ;
					MuestraRecursivo(fila,colum-1) ;
					MuestraRecursivo(fila,colum+1) ;	
				}
			}
		}
	}
}
	
// Muestra todas las casillas que no son bomba
void Tablero::Derrota () {
	for (int i = 0 ; i < tamanio ; i++) {
		for (int j = 0 ; j < tamanio ; j++) {
			if (matriz[i][j].mostrada == false && matriz[i][j].valor != Square_Bomb) {
				CalculaValor(i,j) ; 
				// Funcion mostrar (imagen) 
			}
		}
	}
	// Congelar, imagen derrota y reintentar
}
	
// Todas las casillas mostradas menos las bombas, devuelve un bool para el main
bool Tablero::Victoria () {
	bool victoria = true ;
	for (int i = 0 ; i < tamanio ;  i++) {
		for (int j = 0 ; j < tamanio; j++) {
			if (matriz[i][j].valor != Square_Bomb && matriz[i][j].mostrada == false)
				victoria = false ;
		}
	}
	return victoria ;
}

/*
// Para probar
int main () {
	Tablero juego(8,8) ;	// 5 bombas, 8x8

	for (int i = 0 ; i < 8 ; i++) {
		for (int j = 0 ; j < 8 ; j++) 
				cout << juego.matriz[i][j].valor << " " ;
		cout << endl ;
	}
	
}*/
