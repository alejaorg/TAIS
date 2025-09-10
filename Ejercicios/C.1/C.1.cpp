
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <climits>

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

int ebanistoPropio(vector<int> const& D, Matriz<int>& P) {
	int tam = D.size();
	for (int k = 1; k < tam; ++k) {
		int i = 0;
		int j = k + 1;
		while (i < tam && j < tam) {
			int min = INT_MAX;
			for (int d = i + 1; d < j; d++) {
				if (min > (P[i][d] + P[d][j])) min = P[i][d] + P[d][j];
			}
			P[i][j] = min + ((D[j] - D[i]) * 2);
			++i;
			++j;
		}
	}
	return P[0][D.size() - 1];
}


bool resuelveCaso() {
	// leer los datos de la entrada
	int tam, cortes;

	cin >> tam >> cortes;
	if (tam == 0 && cortes == 0)
		return false;
	vector<int> tablones;
	tablones.push_back(0);
	for (int i = 0; i < cortes; i++) {
		int aux;
		cin >> aux;
		tablones.push_back(aux);
	}
	tablones.push_back(tam);
	// resolver el caso posiblemente llamando a otras funciones
	Matriz<int> matriz(cortes + 2, cortes + 2,0);
	// escribir la solución
	int res = ebanistoPropio(tablones, matriz);
	cout << res << endl;

	//cout << res << "\n";
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
