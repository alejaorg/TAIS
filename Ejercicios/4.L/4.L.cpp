
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <deque>
#include <climits>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */
class CaminoMasCorto {
public:
	CaminoMasCorto(Grafo const& g, int s) : visit(g.V(), false),
		ant(g.V()), dist(g.V()), s(s) {
		bfs(g);
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}
	// número de aristas entre s y v
	int distancia(int v) const {
	return dist[v];
	}
	using Camino = std::deque<int>;
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
	std::vector<int> ant; // ant[v]  = último vértice antes de llegar a v
	std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto
	int s;

	void bfs(Grafo const& g) {
	std::queue<int> q;
	dist[s] = 0; visit[s] = true;
	q.push(s);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int w : g.ady(v)) {
			if (!visit[w]) {
				ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
				q.push(w);
			}
		}
	}
	}
};


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int vert, arist, A, L, T;

	cin >> vert >> arist >> A >> L >> T;
	if (!std::cin)  // fin de la entrada
		return false;

	Grafo grafo(vert);
	for (int i = 0; i < arist; i++) {
		int vert1, vert2;
		cin >> vert1 >> vert2;
		grafo.ponArista(vert1 - 1, vert2 - 1);
	}
	A--;
	L--;
	T--;

	CaminoMasCorto Alex(grafo, A);
	CaminoMasCorto Lucas(grafo, L);
	CaminoMasCorto Trabajo(grafo, T);
	// resolver el caso posiblemente llamando a otras funciones
	int res = INT_MAX;
	for (int i = 0; i < vert; i++) {
		res = min(res, (int)((Alex.camino(i).size() - 1) + (Lucas.camino(i).size() - 1) + (Trabajo.camino(i).size() - 1)));
	}
	// escribir la solución
	cout << res << endl;

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
