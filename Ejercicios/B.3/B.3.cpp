
/*@ <authors>
 *
 * Jorge Perez Ramirez F32 Alejandro Orgaz Fernández F29
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
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

int rellenarMatriz(vector<int> const& cubos, int const& i, int const& j, Matriz<int> & m) {
	if (i >= cubos.size() || j < 0)
		return 0;
	
	int& res = m[i][j];
	if (res == -1) {
		if (i > j)
			res = 0;
		else if (i == j)
			res = cubos[i];
		else {
			
			int sol1 = cubos[i], sol2 = cubos[j];

			sol1 += cubos[i + 1] >= cubos[j] ? rellenarMatriz(cubos, i + 2, j, m) : rellenarMatriz(cubos, i + 1, j - 1, m);

			sol2 += cubos[i] >= cubos[j - 1] ? rellenarMatriz(cubos, i + 1, j - 1, m) : rellenarMatriz(cubos, i, j - 2, m);

			res = max(sol1, sol2);
		}
	}
	return res;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int C;
	cin >> C;
	if (C == 0)
		return false;

	vector<int> cubos(C);
	for (int& a : cubos) {
		cin >> a;
	}

	Matriz<int> m(C, C, -1);

	int sol = rellenarMatriz(cubos, 0, C - 1, m);
	// resolver el caso posiblemente llamando a otras funciones

	cout << sol << "\n";
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
