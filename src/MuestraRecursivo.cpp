// Buscaminas - v.0.3
// Probando rellenar con recursividad

// Condiciones
// 	Posicion valida
//	No está mostrada
//	No tiene bandera

// Precondiciones, no es bomba ?

// void MuestraRecursivo (Posicion p) {
void MuestraRecursivo (int i , int j) {
	if (&matriz[i][j]) {
		if (matriz[i][j].bandera = false && matriz[i][j].mostrada = false ) {
			if (matriz[i][j].valor != Square_Bomb) {
			
				// Calcula el numero			
				for (int pos_i = i - 1 ; pos_i <= i+1 ; pos_i++) {
					for (int pos_j = j-1 ; pos_j <= j-1 ; pos_j++) 			
						if (matriz[pos_i][pos_j] == Square_Bomb)
							matriz[pos_i][pos_j].valor++ ;

				// Mostrar posicion

								// Creo que sobra: if (matriz[fil][col].valor == 0)
				MuestraRecursivo(i-1,j) ;
				MuestraRecursivo(i+1,j) ;
				MuestraRecursivo(i,j-1) ;
				MuestraRecursivo(i,j+1) ;	
				
}
