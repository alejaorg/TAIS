
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernandez F29 y Jorge Perez Ramirez F32
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <limits>
#include <cmath>

using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"


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
		dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	bool hayCamino(int v) const { return dist[v] != INF; }
	Valor distancia(int v) const { return dist[v]; }
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
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int A, C;

	cin >> A >> C;
	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> g(A + 2);
	for (int i = 0; i < C; i++) {
		int v1, v2, dist;
		cin >> v1 >> v2 >> dist;

		g.ponArista({ v1 - 1, v2 - 1, dist });
		g.ponArista({ v2 - 1, v1 - 1, dist });
	}
 
	vector<bool> neutrales(A, true);
	int galos;
	cin >> galos;
	for (int i = 0; i < galos; i++) {
		int aux;
		cin >> aux;
		
		neutrales[aux - 1] = false;
		g.ponArista({ A, aux - 1, 0});
	}
	int romanos;
	cin >> romanos;
	for (int i = 0; i < romanos; i++) {
		int aux;
		cin >> aux;

		neutrales[aux - 1] = false;
		g.ponArista({ A + 1, aux - 1, 0 });
	}
	// resolver el caso posiblemente llamando a otras funciones
	Dijkstra<int> dG(g, A);
	Dijkstra<int> dR(g, A + 1);

	// escribir la solución
	pair<int, int> res = {-1, INT_MAX};
	for (int i = 0; i < A; i++) {
		if (neutrales[i]) {
			if (dG.hayCamino(i) && dR.hayCamino(i)) {
				int diff = abs(dG.distancia(i) - dR.distancia(i));
				if (diff < res.second || (diff == res.second && i < res.first)) {
					res = { i, diff };
				}
			}
		}
	}

	cout << res.first + 1 << " " << res.second << "\n";
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
