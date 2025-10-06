
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * F29 Alejandro Orgaz Fernández y F32 Jorge Perez Ramirez
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>

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
class CaminosDFS {
private:
	std::vector<bool> color;
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
	int s; // vértice origen
	void dfs(Grafo const& G, int v, bool& bipartito) {
		if (bipartito) {
			visit[v] = true;
			for (int w : G.ady(v)) {
				if (!visit[w]) {
					ant[w] = v;
					color[w] = !color[v];
					dfs(G, w, bipartito);
				}
				else if (bipartito){
					bipartito = color[w] != color[v];
				}
			}
		}
	}
public:
	CaminosDFS(Grafo const& g, int s, bool &bipartito) : visit(g.V(), false),
		ant(g.V()), s(s), color(g.V(), false) {
		dfs(g, s, bipartito);
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}
	using Camino = std::deque<int>; // para representar caminos
	// devuelve un camino desde el origen a v (debe existir)
	Camino camino(int v) const {
		if (!hayCamino(v))
			throw std::domain_error("No existe camino");
		Camino cam;
		// recuperamos el camino retrocediendo
		for (int x = v; x != s; x = ant[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A;

	cin >> V >> A;
	if (!std::cin)  // fin de la entrada
		return false;

	Grafo g(V);
	for (int i = 0; i < A; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		g.ponArista(v1, v2);
	}
	// resolver el caso posiblemente llamando a otras funciones
	unordered_set<int> visitados;
	bool res = true;
	int aux;
	for (int i = 0; i < V; i++) {
		visitados.insert(i);
	}
	aux = *visitados.begin();
	while (!visitados.empty() && res) {
		CaminosDFS camino(g, aux, res);
		for (int i = 0; i < V && res; i++) {
			if (camino.hayCamino(i) && visitados.count(i) == 1) {
				visitados.erase(i);
			}
		}
		if (!visitados.empty())	aux = *visitados.begin();
	}
	

	// escribir la solución
	res ? cout << "SI\n" : cout << "NO\n";

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

