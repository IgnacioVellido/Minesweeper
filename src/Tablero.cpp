// Buscaminas - v.0.4.1
// 27/4/2017 - 
// Para compilar (debido al aleatorio) -std=c++11

// NO INCLUIR ESTO - PRUEBA
#include <iostream>
using namespace std ;

// Iniciar aleatorio
#include <random> 

// Esto está en el main !
enum Squares {
	Square_0 ,
	Square_1 ,
	Square_2 ,
	Square_3 ,
	Square_4 ,
	Square_5 ,
	Square_6 ,
	Square_7 ,
	Square_8 ,
	Square_Bomb ,
	Square_Flag ,
	Square_Border
} ;

struct Posicion {
	int valor ;
	bool bandera ;
	bool mostrada ;
//	SDL_Surface * Imagen ; // Puntero a la imagen

	// Necesita constructor
	Posicion () : valor(0), bandera(false), mostrada(false) {} 
} ;

class Tablero {
private:
	int nivel , // Define el numero de bombas 
	    tamanio ; // Define el tamaño de la matriz , intentar que sea constante

	// Genera un nº aleatorio entre las filas/colum posibles
	// Si tam = 10, genera números del 0 al 9 
	int GeneraAleatorio (){
		random_device rd;  //Will be used to obtain a seed for the random number engine
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> dis(0, tamanio-1); 
		return (dis(gen)) ;
	}

	// Añade bombas en posiciones aleatorias hasta un maximo definido por el nivel  - FUNCIONA
	void InsertBomb () {
		int fila , colum ,
		    contador = 0 ;

		while (contador != nivel) {
			fila = GeneraAleatorio() ;
			colum = GeneraAleatorio() ;
			// Se podria acceder con punteros (?) 
			if (matriz[fila][colum].valor != Square_Bomb) { 
				matriz[fila][colum].valor = Square_Bomb ; contador++ ; cout << "bum" << endl ;
			} 
		}
	}
	// Precondición: No es bomba
	void CalculaValor (int fila, int colum) {
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
public:
	// Matriz, comienza con vector de punteros	
	Posicion **matriz ;

	Tablero (int bomb, int tam) : nivel(bomb) , tamanio(tam) {
		matriz = new Posicion * [tamanio] ;
		// NO INCLUIR ESTO - PRUEBA
		for (int i = 0 ; i < tamanio ; i++) {
			matriz[i] = new Posicion [tamanio] ;
			for (int j = 0 ; j < tamanio ; j++) 
				matriz[i][j].valor = 0 ; 
		}
		InsertBomb() ;
	}

	~Tablero() {
		for (int i = 0 ; i < tamanio ; i++)
			delete[] matriz[i] ;
		delete[] matriz ;
	}

	//	void MuestraRecursivo (int, int) ; Si lo saco - no compila ARREGLAR
	// Empiezan en 0 - FUNCIONA
	void MuestraRecursivo (int fila , int colum) {
		bool accesible = (fila >= 0 && fila < tamanio) && (colum >= 0 && colum < tamanio) ;
		if (accesible) {
			if (matriz[fila][colum].bandera == false && matriz[fila][colum].mostrada == false ) {
				if (matriz[fila][colum].valor != Square_Bomb) {
					cout << "estoy en: " << fila << colum <<  endl ;
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

	// FUNCIONA 
	void Bandera (int i, int j) {
		matriz[i][j].bandera = !matriz[i][j].bandera ;
	}
	
	// Muestra todas las casillas que no son bomba
	void Derrota () {
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
	bool Victoria () {
		bool victoria = true ;
		for (int i = 0 ; i < tamanio ;  i++) {
			for (int j = 0 ; j < tamanio; j++) {
				if (matriz[i][j].valor != Square_Bomb && matriz[i][j].mostrada == false)
					victoria = false ;
			}
		}
		return victoria ;
	}
} ;


// Para probar
int main () {
	Tablero juego(8,8) ;	// 5 bombas, 8x8

	for (int i = 0 ; i < 8 ; i++) {
		for (int j = 0 ; j < 8 ; j++) 
				cout << juego.matriz[i][j].valor << " " ;
		cout << endl ;
	}
	
}

	// Funcion menu: Indica instrucciones (probar con multihilo)
	// Funcion derrota: Muestra todo, congela pantalla, reintentar
