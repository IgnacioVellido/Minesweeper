// Buscaminas - v.0.3
// 27/4/2017 - 
// Mejorar algoritmo de aleatorio, casi siempre salen los mismos

// NO INCLUIR ESTO - PRUEBA
#include <iostream>
using namespace std ;

// Iniciar aleatorio
#include <ctime>
#include <cstdlib>

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

// Genera un nº aleatorio entre las filas/colum posibles
// Si tam = 10, genera números del 0 al 9 
// CUIDADO CON LOS PARAMETROS
int GeneraAleatorio (time_t &t){
	const int MY_MAX_RAND = 4 ;	// Arreglar
	// time_t t ;
	srand ((int) time(&t));

	return (rand() % MY_MAX_RAND) ;
}

class Tablero {
private:
	int nivel , // Define el numero de bombas 
	    tamanio ; // Define el tamaño de la matriz , intentar que sea constante
//	Posicion matriz [tamanio] [tamanio] ;

	// Añade bombas en posiciones aleatorias hasta un maximo definido por el nivel  - FUNCIONA
	void InsertBomb () {
		int fila , colum ,
		    contador = 0 ;

		while (contador != nivel) {
			fila = GeneraAleatorio(time_t t1) ;
			colum = GeneraAleatorio(time_t t2) ;
			// Se podria acceder con punteros (?)
			if (matriz[fila][colum].valor != Square_Bomb) {
				matriz[fila][colum].valor = Square_Bomb ; contador++ ; cout << "bum" << endl ;
			} 
		}
	}
public:
// NO INCLUIR ESTO - PRUEBA
	Posicion matriz [8] [8] ;

	Tablero (int bomb, int tam) : nivel(bomb) , tamanio(tam) {
		// NO INCLUIR ESTO - PRUEBA
		for (int i = 0 ; i < tamanio ; i++) {
			for (int j = 0 ; j < tamanio ; j++) 
				matriz[i][j].valor = 0 ;
		}
		InsertBomb() ;
	}
	//	void MuestraRecursivo (int, int) ; Si lo saco - no compila ARREGLAR
	// Empiezan en 0 - FUNCIONA - MEJORAR
	void MuestraRecursivo (int i , int j) {
		//if (&matriz[i][j]) { No furula
		bool accesible = (i >= 0 && i < tamanio) && (j >= 0 && j < tamanio) ;
		if (accesible) {
			if (matriz[i][j].bandera == false && matriz[i][j].mostrada == false ) {
				if (matriz[i][j].valor != Square_Bomb) {
					cout << "estoy en: " << i << j <<  endl ;
					// Calcula el numero			
					for (int pos_i = i - 1 ; pos_i <= i+1 ; pos_i++) { 
						for (int pos_j = j-1 ; pos_j <= j+1 ; pos_j++) 	{ 
							accesible = (pos_i >= 0 && pos_i < tamanio) && (pos_j >= 0 && pos_j < tamanio) ;
							// if (&matriz[pos_i][pos_j]) { NOPE
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
	friend int GeneraAleatorio () ;
} ;


// Para probar
int main () {
	Tablero juego(5,8) ;	// 5 bombas, 8x8
	juego.MuestraRecursivo(0,1) ;
	juego.MuestraRecursivo(2,7) ;
	juego.MuestraRecursivo(5,3) ;

	for (int i = 0 ; i < 8 ; i++) {
		for (int j = 0 ; j < 8 ; j++) 
				cout << juego.matriz[i][j].valor << " " ;
		cout << endl ;
	}
	
}

	// Funcion menu: Indica instrucciones (probar con multihilo)
	// Funcion derrota: Muestra todo, congela pantalla, reintentar
