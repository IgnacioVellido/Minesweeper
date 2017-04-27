#ifndef TABLERO_H
#define TABLERO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Interfaz.h"
// Iniciar aleatorio
#include <random> 
using namespace std ;
/*
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
*/
struct Posicion {
	int valor ;
	bool bandera ;
	bool mostrada ;
	SDL_Rect casilla ; // Casilla a editar

	// Necesita constructor
	Posicion () : valor(0), bandera(false), mostrada(false) {} 
} ;

class Tablero {
private:
	int nivel , // Define el numero de bombas 
	    tamanio ; // Define el tamaño de la matriz , intentar que sea constante

	// Genera un nº aleatorio entre las filas/colum posibles
	// Si tam = 10, genera números del 0 al 9 
	int GeneraAleatorio () ;

	// Añade bombas en posiciones aleatorias hasta un maximo definido por el nivel  - FUNCIONA
	void InsertBomb () ;

	// Precondición: No es bomba
	void CalculaValor (int fila, int colum) ;
public:
	// Matriz, comienza con vector de punteros	
	Posicion **matriz ;

	Tablero (int bomb, int tam) : nivel(bomb) , tamanio(tam) {
		matriz = new Posicion * [tamanio] ;
		for (int i = 0 ; i < tamanio ; i++) {
			matriz[i] = new Posicion [tamanio] ;
			for (int j = 0 ; j < tamanio ; j++) 
				matriz[i][j].valor = Square_Hide; 
		}
		InsertBomb() ;
	}

	~Tablero() {
		for (int i = 0 ; i < tamanio ; i++)
			delete[] matriz[i] ;
		delete[] matriz ;
	}
	
	// Actualiza las imágenes
	void Actualiza () ;

	void MuestraRecursivo (int fila , int colum) ;

	// FUNCIONA 
	void Bandera (int i, int j) {
		matriz[i][j].bandera = !matriz[i][j].bandera ;		
	}
	
	// Muestra todas las casillas que no son bomba
	void Derrota () ;
	
	// Todas las casillas mostradas menos las bombas, devuelve un bool para el main
	bool Victoria () ;
} ;

#endif
