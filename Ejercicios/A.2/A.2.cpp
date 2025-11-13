
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

#include "Matriz.h"
#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
EntInf min_Dardos(vector<int> const& M, int C, Matriz<EntInf> &dardos) {
	int n = M.size();
	dardos[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		dardos[i][0] = 0;
		for (int j = 1; j <= C; ++j)
			if (M[i - 1] > j)
				dardos[i][j] = dardos[i - 1][j];
			else
				dardos[i][j] = min(dardos[i - 1][j], dardos[i][j - M[i - 1]] + 1);
	}
	return dardos[n][C];
}

vector<EntInf> recSol(vector<int> const& M, int C, Matriz<EntInf>& dardos) {
	int i = M.size();
	int j = C;
	vector<EntInf> sol;
	while (dardos[i][j] != 0) {
		if (j - M.at(i - 1) >= 0 && (dardos[i][j] == (dardos[i][j - M.at(i - 1)] + 1))) {
			sol.push_back(M.at(i - 1));
			j -= M.at(i - 1);
		}
		else {
			i--;
		}
	}
	return sol;
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int Obj, S;

	cin >> Obj >> S;
	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> sectores;
	for (int i = 0; i < S; i++) {
		int aux;
		cin >> aux;
		sectores.push_back(aux);
	}
	sort(sectores.begin(), sectores.end(), less<int>());
	// resolver el caso posiblemente llamando a otras funciones
	Matriz<EntInf> dardos(sectores.size() + 1, Obj + 1, Infinito);
	EntInf min = min_Dardos(sectores, Obj, dardos);
	// escribir la solución
	if (min != Infinito) {
		cout << min << ": ";
		vector<EntInf> sol = recSol(sectores, Obj, dardos);
		for (EntInf i : sol) {
			cout << i << " ";
		}
	}
	else {
		cout << "Imposible";
	}
	cout << "\n";
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
