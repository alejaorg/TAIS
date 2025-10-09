
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernández F29 y Jorge Pérez Ramírez F32
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminoMasCorto {
public:
	using Camino = deque<int>;
	CaminoMasCorto(Grafo const& g, int s,const int &TTl, int &res) : visit(g.V(), false),
		ant(g.V()), dist(g.V()), s(s), TTL(TTl) {
		bfs(g, res);
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}
		// número de aristas entre s y v
		int distancia(int v) const {
		return dist[v];
	}
	// devuelve el camino más corto desde el origen a v (si existe)
	Camino camino(int v) const {
		if (!hayCamino(v)) throw std::domain_error("No existe camino");
		Camino cam;
		for (int x = v; x != s; x = ant[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}
private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
	std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto
	int s;
	int TTL;
		void bfs(Grafo const& g, int &res) {
		std::queue<int> q;
		dist[s] = 0; visit[s] = true;
		res++;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w] && dist[v] < TTL) {
					ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
					q.push(w);
					res++;
				}
			}
		}
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, C;

	cin >> N >> C;
	if (!std::cin)  // fin de la entrada
		return false;

	Grafo g(N);

	for (int i = 0; i < C; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		g.ponArista(v1 - 1, v2 - 1); 
	}
	int consultas;
	cin >> consultas;

	for (int i = 0; i < consultas; i++) {
		int v, TTL, res = 0;

		cin >> v >> TTL;
		CaminoMasCorto camino(g, v - 1, TTL, res);
		cout << N - res << "\n";
	}
	// resolver el caso posiblemente llamando a otras funciones

	// escribir la solución
	cout << "---\n";

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

