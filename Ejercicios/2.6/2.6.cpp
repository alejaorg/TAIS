
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


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct tPartido {

	double nEscanios = 0;
	double nVotos = 0;
	int indice;

};

struct Comparator {
	bool operator()(tPartido e1, tPartido e2) {
		double f1 = e1.nVotos / (e1.nEscanios + 1);
		double f2 = e2.nVotos / (e2.nEscanios + 1);
		if (f1 == f2) {
			if (e1.nVotos == e2.nVotos) { 
				return e1.indice > e2.indice; 
			}
			else {
				return e1.nVotos < e2.nVotos;
			}
		}
		else return f1 < f2;
	}
};

struct OrdenIndex {
	bool operator()(tPartido e1, tPartido e2) {
		return e1.indice > e2.indice;
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, N;

	cin >> V >> N;
	if (V == 0 && N == 0)
		return false;

	priority_queue<tPartido, vector<tPartido>, Comparator> cola;
	for (int i = 0; i < V; i++) {
		tPartido aux;
		cin >> aux.nVotos;
		aux.indice = i;
		cola.push(aux);
	}
	// resolver el caso posiblemente llamando a otras funciones
	while (N > 0) {
		tPartido aux = cola.top();
		cola.pop();
		aux.nEscanios++;
		cola.push(aux);
		N--;
	}
	// escribir la solución
	priority_queue<tPartido, vector<tPartido>, OrdenIndex> res;
	while (!cola.empty()) {
		res.push(cola.top());
		cola.pop();
	}
	for (int i = 0; i < V; i++) {
		cout << res.top().nEscanios;
		res.pop();
		if (i < V - 1) cout << " ";
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
