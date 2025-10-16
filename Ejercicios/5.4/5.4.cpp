
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Jorge Pérez Ramírez F32
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

class CaminoMasCorto {
public:
	CaminoMasCorto(Grafo const& g, int s, int const& T, vector<pair<int, int>> const& opers, int & res) : visit(g.V(), false),
		ant(g.V()), dist(g.V()), s(s) {
		bfs(g, T, opers, res);
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}
	
	// número de aristas entre s y v
	int distancia(int v) const {
	return dist[v];
	}
	using Camino = deque<int>;
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

	void bfs(Grafo const& g, int const& T, vector<pair<int,int>> opers, int & res) {
		std::queue<int> q;
		dist[s] = 0; visit[s] = true;
		q.push(s);
		while (!q.empty() && res == -1) {
			int v = q.front(); q.pop();
			int aux = v;
			if (aux == T)
				res = dist[aux];
			else {
				for (pair<int, int> w : opers) {
					aux = (v * w.first + w.second) % g.V();
					if (!visit[aux]) {
						ant[aux] = v; dist[aux] = dist[v] + 1; visit[aux] = true;
						q.push(aux);
					}
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

		int M, S, T;

		cin >> M >> S >> T;

		if (!std::cin)  // fin de la entrada
			return false;

		Grafo g(M);

		int res = -1, nOpers;
		cin >> nOpers;
		vector<pair<int, int>> opers(nOpers);

		for (pair<int, int> & a : opers) 
			cin >> a.first >> a.second;
		
		CaminoMasCorto camino(g, S, T, opers, res);

		cout << res << "\n";
		// resolver el caso posiblemente llamando a otras funciones

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

