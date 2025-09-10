
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <math.h>


using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;

	cin >> n;
	if (!std::cin)  // fin de la entrada
		return false; 
	
	Matriz<int> matriz(n + 2,n + 2, -1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int aux;
			cin >> aux;
			matriz.at(i, j) = aux;
		}
	}
	// resolver el caso posiblemente llamando a otras funciones
	Matriz <int> dp(n + 2, n + 2, -1);
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			dp.at(i + 1, j) = matriz.at(i + 1, j) + max(matriz.at(i,j), max (matriz.at(i , j - 1), matriz.at(i ,j +1)));
			matriz.at(i + 1, j) = dp.at(i + 1, j);
		}
	}

	// escribir la solución
	int maximo = 0;
	for (int i = 1; i <= n; i++) {
		maximo = matriz.at(n, maximo) < matriz.at(n, i) ? i : maximo;
	}
	cout << matriz.at(n, maximo) << " " << maximo << "\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
