// Buscaminas - v.0.4
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
	//	void MuestraRecursivo (int, int) ; Si lo saco - no compila ARREGLAR
	// Empiezan en 0 - FUNCIONA - MEJORAR
	void MuestraRecursivo (int i , int j) {
		bool accesible = (i >= 0 && i < tamanio) && (j >= 0 && j < tamanio) ;
		if (accesible) {
			if (matriz[i][j].bandera == false && matriz[i][j].mostrada == false ) {
				if (matriz[i][j].valor != Square_Bomb) {
					cout << "estoy en: " << i << j <<  endl ;
					// Calcula el numero			
					for (int pos_i = i - 1 ; pos_i <= i+1 ; pos_i++) { 
						for (int pos_j = j-1 ; pos_j <= j+1 ; pos_j++) 	{ 
							accesible = (pos_i >= 0 && pos_i < tamanio) && (pos_j >= 0 && pos_j < tamanio) ;
							if (accesible && i != j) {
								if (matriz[pos_i][pos_j].valor == Square_Bomb)
									matriz[i][j].valor++ ;
							}
						}
					}

					// Mostrar posicion
					matriz[i][j].mostrada = true ;

					// En el original, si es un número no muestra más
					if (matriz[i][j].valor == 0) {
						MuestraRecursivo(i-1,j) ;
						MuestraRecursivo(i+1,j) ;
						MuestraRecursivo(i,j-1) ;
						MuestraRecursivo(i,j+1) ;	
					}
				}
			}
		}
	}

	// FUNCIONA 
	void Bandera (int i, int j) {
		matriz[i][j].bandera = !matriz[i][j].bandera ;
	}

	//void Derrota
	//bool Victoria () {}	// Todas las casillas mostradas menos las bombas, devuelve un bool para el main
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
