
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernandez F29
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

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
	int mW, N;

	cin >> mW >> N;
	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> people(N);
	for (int i = 0; i < N; i++) {
		int weigth;
		cin >> weigth;
		people.at(i) = weigth;
	}

	// resolver el caso posiblemente llamando a otras funciones
	sort(people.begin(), people.end(), less<int>());
	int i = 0; 
	int j = N - 1;
	int res = 0;
	while (i < j) {
		if (people.at(i) + people.at(j) <= mW) {
			res++;
			i++;
			j--;
		}
		else {
			j--;
		}
	}
	
	// escribir la solución
	cout << res + (N - (res * 2)) << "\n";

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
