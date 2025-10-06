
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
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
	int s; // vértice origen
	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				ant[w] = v;
				dfs(G, w);
			}
		}
	}
public:
	CaminosDFS(Grafo const& g, int s) : visit(g.V(), false),
		ant(g.V()), s(s) {
		dfs(g, s);
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

class MaximaCompConexa {
public:
	MaximaCompConexa(Grafo const& g) : visit(g.V(), false), maxim(0) {
		for (int v = 0; v < g.V(); ++v) {
			if (!visit[v]) { // se recorre una nueva componente conexa
				int tam = dfs(g, v);
				maxim = max(maxim, tam);
			}
		}
	}
	// tamaño máximo de una componente conexa
	int maximo() const {
		return maxim;
	}
private:
	vector<bool> visit; // visit[v] = se ha visitado el vértice v?
	int maxim; // tamaño de la componente mayor
	int dfs(Grafo const& g, int v) {
		visit[v] = true;
		int tam = 1;
		for (int w : g.ady(v)) {
			if (!visit[w])
				tam += dfs(g, w);
		}
		return tam;
	}
};
void resuelveCaso() { // O(N + M)
	int N, M;
	cin >> N >> M;
	Grafo amigos(N);
	int v, w;
	for (int i = 0; i < M; ++i) {
		cin >> v >> w;
		amigos.ponArista(v - 1, w - 1);
	}
	MaximaCompConexa mcc(amigos);
	cout << mcc.maximo() << '\n';
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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}

