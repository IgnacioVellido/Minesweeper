// Buscaminas - v.0.1
// Probando rellenar con recursividad

// Condiciones
// 	Posicion valida
//		No hay numero
//		No tiene bandera

// Precondiciones, no es bomba

// void MuestraRecursivo (Posicion p) {
void MuestraRecursivo (int i , int j) {
	//int i = p.fil , j = p.col ;
	if (&matriz[fil][col]) {
		if (p.bandera = false) {
			// Mostrar posicion
			if (matriz[fil][col] == 0) {
				// Calcula posicion ?? No debería y no sería recomendable
				// Muestra posicion (?)
				//Posicion nueva = p ;
				MuestraRecursivo(i-1,j) ;
				MuestraRecursivo(i+1,j) ;
				MuestraRecursivo(i,j-1) ;
				MuestraRecursivo(i,j+1) ;	
			}
}
