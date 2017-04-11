// Buscaminas - v.0.1
// 27/4/2017 - 

// Al hacer click izq sobre una bandera, no desvelar
// No mostrar las marcadas con casillas
// Moduralizar - clase, metodos, main
//http://www.chiark.greenend.org.uk/~sgtatham/puzzles/doc/mines.html#mines

// Iniciar aleatorio
#include <ctime>
#include <cstdlib>

// Contiene sus coordenadas, y si se encuentra marcado (deberia ser por defecto false, comprobar si funciona)
struct Posicion {
	int fil, col ;
	bool bandera = false ;
}

// Genera un nº aleatorio entre las filas/colum posibles (COMPROBAR)
// Si se quiere probar con vector - tam*tam+1
void GeneraAleatorio (){
	const int MY_MAX_RAND = tamanio + 1 ;
	time_t t ;
	srand ((int) time(&t));

	return (rand() % MY_MAX_RAND) ;
}

class Tablero {
private:
	int nivel , // Define el numero de bombas 
	    tamanio ; // Define el tamaño de la matriz , intentar que sea constante
	Posicion matriz [tamanio] [tamanio] ;
	bool mostrados [tamanio] [tamanio] ;

	// Añade bombas en posiciones aleatorias hasta un maximo definido por el nivel 
	void AniadeBomb () {
		int fila , colum ,
		    contador = 0 ;

		while (contador != nivel) {
			fila = GeneraAleatorio() ;
			colum = GeneraAleatorio() ;
			// Se podriaa acceder con punteros (?)
			if (matriz[fila][colum] != -1) {
				matriz[fila][colum] = -1 ; contador++ ;
			} 
		}
	}

	// Cuenta el numero de bombas adyacentes
	// Condiciones: - NO ser bomba (-1) - Posicion accesible
	void RellenaTablero () {
		int recorre_fil = 0 , recorre_colum = 0 ,

		for (recorre_fil ; recorre_fil < tamanio - 1 ; recorre_fil++) {
			for (recorre_colum ; recorre_colum < tamanio - 1 ; recorre_colum) {
				if (matriz[recorre_fil][recorre_colum] != -1)
					matriz[recorre_fil][recorre_colum] = Ocurrencias(recorre_fil,recorre_colum) ;
			}
		}
	}

	// Cuenta el numero de bombas alredor de la posicion dada - Evitar repeticion de codigo
	// Primero mira si es posicion valido, luego mira si es bomba (-1)
	int Ocurrencias (int fil, int col) {
		int contador = 0 ;
		
		// Parte izquierda			
		if (&matriz[fil-1][col-1]) {
			if (matriz[fil-1][col-1] == -1) contador++ ;
		}
		if (&matriz[fil][col-1]) {
			if (matriz[fil][col-1] == -1) contador++ ;
		}
		if (&matriz[fil+1][col-1]) {
			if (matriz[fil+1][col-1] == -1) contador++ ;
		}
		
		// Parte derecha
		if (&matriz[fil-1][col+1]) {
			if (matriz[fil-1][col+1] == -1) contador++ ;
		}
		if (&matriz[fil][col+1]) {
			if (matriz[fil][col+1] == -1) contador++ ;
		}
		if (&matriz[fil+1][col+1]) {
			if (matriz[fil+1][col+1] == -1) contador++ ;
		}

		// Parte superior
		if (&matriz[fil-1][col]) {
			if (matriz[fil][col] == -1) contador++ ;
		}
		if (&matriz[fil+1][col]) {
			if (matriz[fil+1][col] == -1) contador++ ;
		}

		return contador ;
	}
	
	
public:
	Tablero (int bomb, int tam) : nivel(bomb) , tamanio(tam) {
		// Iniciar mostrados a 0
		for (int i = 0 ; i < tamanio ; i++) {
			for (int j = 0 ; j < tamanio ; j++)
				mostrados[i][j] = false ;
		}
	}
	// Mostar hasta que encuentra numeros
	//void Mostrar
	// Si es bomba, mostrar
	//void Derrota
	bool Victoria () {}	
	friend GeneraAleatorio () ;
}

// Funcion menu: Indica instrucciones, forma de salir
// Funcion victoria: Muestra victoria (deberia mostrar tiempo)
// Funcion derrota: Muestra bombas (o todo), congela pantalla, reintentar

int main () {
	// Inicializar pantalla 		
	// Despliga menu
	// Pide nivel - Construye Tablero
	
	
}

