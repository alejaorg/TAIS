
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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

struct comparator {

	bool operator()(pair<int, int> e1, pair<int, int> e2) {
		if (e1.second == e2.second) {
			return e1.first < e2.first;
		}
		else return e1.second < e2.second;
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, C;

	cin >> N >> C;
	if (N == 0 && C == 0)
		return false;

	PriorityQueue<pair<int,int>, comparator> cola;
	queue<int> clientes;
	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < C; i++) {
		int aux; 
		cin >> aux;
		clientes.push(aux);
	}
	for (int i = 0; i < N; i++) cola.push({ i,0 });


	int contador = 0;
	while (!clientes.empty()) {
		pair<int,int> acum = cola.top();
		cola.pop();
		cola.push({ acum.first, acum.second + clientes.front() });
		clientes.pop();
	}

	// escribir la solución
	cout << cola.top().first + 1 << endl;

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
