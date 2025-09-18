
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "TreeSet_AVLkesimo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int CENTINELA = 0;

bool resuelveCaso() {
	// leer los datos de la entrada

	int N;

	cin >> N;
	if (N == CENTINELA)
		return false;

	Set<int> arbol;
	for (int i = 0; i < N; i++) {
		int aux;
		cin >> aux;
		arbol.insert(aux);
	}
	// resolver el caso posiblemente llamando a otras funciones
	int M;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int aux;
		cin >> aux;
		try {
			int res = arbol.kesimo(aux);
				cout << res << endl;

		} 
		catch (out_of_range) {
			cout << "??" << endl;
		}

	}
	
	cout << "---" << endl;

	// escribir la solución

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
