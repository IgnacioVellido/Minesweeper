#include "Tablero.h"

void Tablero::Bandera (int i, int j) {
	if (matriz[i][j].mostrada == false) 	
		matriz[i][j].bandera = !matriz[i][j].bandera ;		
}

int Tablero::GeneraAleatorio () {
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
	bool accesible ; matriz[fila][colum].valor = 0 ;
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
bool Tablero::Derrota (int x, int y) {
	bool derrota = false ;
	if (matriz[x][y].valor == Square_Bomb) {
		for (int i = 0 ; i < tamanio ; i++) {
			for (int j = 0 ; j < tamanio ; j++) {
				if (matriz[i][j].mostrada == false && matriz[i][j].valor != Square_Bomb) {
					CalculaValor(i,j) ; 
				}					
				matriz[i][j].mostrada = true ;
			}
		}
		matriz[x][y].valor = Square_Boom ;
		derrota = true ;
		// Congelar, imagen derrota y reintentar (en el main (?))
	}
	return derrota ;
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
