
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

// propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
/*
int minID(vector<int> v) {
	int min = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < v[min]) min = i;
	}
	return min;
}
*/
struct Comparadordepairs {
	bool operator()(pair<int, int> e1, pair<int, int> e2) {
		return e1.first == e2.first ? e1.second > e2.second : e1.first > e2.first;
	}

};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N; 
	vector<stack<int>> pilas;
	int min = INT_MAX;

	cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;

	for (int i = 0; i < N; i++) {
		int K;
		cin >> K;
		stack<int> pila;
		for (int j = 0; j < K; j++) {
			int elem;
			cin >> elem;
			if (elem < min) {
				min = elem;
			}
			pila.push(elem);
		}
		pilas.push_back(pila);
	}
	// resolver el caso posiblemente llamando a otras funciones
	int cont = 0;
	int res = 0;
	// escribir la solución
	priority_queue<pair<int, int>, vector<pair<int, int>>, Comparadordepairs> auxv;
	for (int i = 0; i < pilas.size(); i++) {
		auxv.push({ pilas[i].top(), i });
		pilas[i].pop();
	}
	int index = auxv.top().second;
	while (auxv.top().first != min) {
		auxv.pop();
		if (!pilas[index].empty()) {
			auxv.push({ pilas[index].top(), index });
			pilas[index].pop();
		}
		index = auxv.top().second;
		cont++;
	}

	cout << cont + 1<< "\n";

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
