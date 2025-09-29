
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
void cargaCola(PriorityQueue<int, greater<int>> & cola, const int pilas) {
	for (int i = 0; i < pilas; i++) {
		int V;
		cin >> V;
		cola.push(V);
	}
}

void cargaColaV(PriorityQueue<int, greater<int>> & cola, vector<int> const& pilas) {
	for (int a : pilas) 
		cola.push(a);
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int N, A, B;
	cin >> N >> A >> B;

	if (!std::cin)  // fin de la entrada
		return false;

	PriorityQueue<int, greater<int>> colaA;
	cargaCola(colaA, A);

	PriorityQueue<int, greater<int>> colaB;
	cargaCola(colaB, B);

	while (!colaA.empty() && !colaB.empty()) {
		vector<int> usadasA;
		vector<int> usadasB;
		int suma = 0;
		for (int i = 0; i < N && !colaA.empty() && !colaB.empty(); i++) {
			int pilaA, pilaB;

			pilaA = colaA.top();
			colaA.pop();

			pilaB = colaB.top();
			colaB.pop();

			suma += min(pilaA, pilaB);
			
			if (pilaA < pilaB) {
				pilaB -= pilaA;
				usadasB.push_back(pilaB);
			}
			
			else if (pilaA > pilaB) {
				pilaA -= pilaB;
				usadasA.push_back(pilaA);
			}
		}
		cout << suma << " ";
		cargaColaV(colaA, usadasA);
		cargaColaV(colaB, usadasB);
	}
	// resolver el caso posiblemente llamando a otras funciones
	cout << "\n";
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
