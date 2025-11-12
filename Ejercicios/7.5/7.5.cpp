
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernandez F29
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class Dijkstra {
public:
	using Camino = deque<AristaDirigida<Valor>>;

	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()), tam(g.V(), g.A()) {
		dist[origen] = 0;
		tam[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
		bool hayCamino(int v) const { return dist[v] != INF; }
	Valor distancia(int v) const { return dist[v]; }
	int tam_v(int v) { return tam[v]; }
	Camino camino(int v) const {
		Camino cam;
		// recuperamos el camino retrocediendo
		AristaDirigida<Valor> a;
		for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
			cam.push_front(a);
		cam.push_front(a);
		return cam;
	}
private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<int> tam;
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;
			tam[w] = tam[v] + 1;
			pq.update(w, dist[w]);
		}
		else if (dist[w] == dist[v] + a.valor()) {
			tam[w] = min(tam[v] + 1, tam[w]);
		}
	}
};

class BFSDirigido {
public:
	using Camino = deque<int>;
	BFSDirigido(DigrafoValorado<int> const& g, int s) : visit(g.V(), false),
		ant(g.V()), dist(g.V()), s(s) {
		bfs(g);
	}
	bool hayCamino(int v) const {
		return visit[v];
	}
	int distancia(int v) const {
		return dist[v];
	}
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
	std::vector<int> dist; // dist[v] = aristas en el camino s->v más corto
	int s;
	void bfs(DigrafoValorado<int> const& g) {
		std::queue<int> q;
		dist[s] = 0; visit[s] = true;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (auto w : g.ady(v)) {
				if (!visit[w.hasta()]) {
					ant[w.hasta()] = v; dist[w.hasta()] = dist[v] + 1; visit[w.hasta()] = true;
					q.push(w.hasta());
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

	DigrafoValorado<int> g(N);

	for (int i = 0; i < C; i++) {
		int v1, v2, cost;
		cin >> v1 >> v2 >> cost;

		g.ponArista({ v1 - 1, v2 - 1, cost });
		g.ponArista({ v2 - 1, v1 - 1, cost });
	}
	// resolver el caso posiblemente llamando a otras funciones
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int orig, dest;
		cin >> orig >> dest;

		Dijkstra<int> d(g, orig - 1);
		if (d.hayCamino(dest - 1)) {
			cout << d.distancia(dest - 1) << " ";
			BFSDirigido b(g, orig - 1);
			if (d.tam_v(dest - 1) == b.distancia(dest - 1)) {
				cout << "SI\n";
			}
			else cout << "NO\n";
		}
		else cout << "SIN CAMINO\n";
	}
	
	cout << "---\n";
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
