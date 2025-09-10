
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>
int rellenarMatriz(Matriz<int>& matriz, int presupuesto, int fest, const vector<pair<int, int>> &caracteristicas) {
	if (matriz[fest][presupuesto] == -1) {
		if (fest == 0 || presupuesto == 0) {
			return 0;
		}
		int res1 = 0;
		int res2 = 0;
		if (presupuesto >= caracteristicas[fest - 1].second) {
			res1 = rellenarMatriz(matriz, presupuesto - caracteristicas[fest - 1].second, fest - 1, caracteristicas) + caracteristicas[fest - 1].first;
		}
		res2 = rellenarMatriz(matriz, presupuesto, fest - 1, caracteristicas);
		matriz[fest][presupuesto] = max(res1, res2);
		return matriz[fest][presupuesto];
		
	}
	else {
		return matriz[fest][presupuesto];
	}
}


bool resuelveCaso() {
	// leer los datos de la entrada
	int pres, N;

	cin >> pres >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	Matriz<int> matriz(N + 1, pres + 1, -1);
	vector<pair<int,int>> caracteristicas(N);
	for (pair<int, int>& a : caracteristicas) cin >> a.first >> a.second;
	// resolver el caso posiblemente llamando a otras funciones
	rellenarMatriz(matriz, pres, N, caracteristicas);

	cout << matriz[N][pres] << "\n";

	// escribir la soluci�n

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
