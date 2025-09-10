
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <limits>
using namespace std;

#include "DigrafoValorado.h"  
#include "IndexPQ.h"
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
template <typename Valor>
class Dijkstra {
public:
	using Camino = deque<AristaDirigida<Valor>>;
	Dijkstra(DigrafoValorado<Valor> const& g, int orig,const vector<int> &tiempos) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
		dist[origen] = tiempos[orig];
		pq.push(origen, tiempos[orig]);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a, tiempos);
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
	void relajar(AristaDirigida<Valor> a, const vector<int> &tiempos) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()  + tiempos[w]) {
			dist[w] = dist[v] + a.valor() + tiempos[w]; ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};




bool resuelveCaso() {
	// leer los datos de la entrada
	int nPag;

	cin >> nPag;
	if (nPag == 0)
		return false;

	vector<int> tiempos_carga;
	for (int i = 0; i < nPag; i++) {
		int time;
		cin >> time;
		tiempos_carga.push_back(time);
	}
	// resolver el caso posiblemente llamando a otras funciones
	
	DigrafoValorado<int> grafo(nPag);

	int nEnl;
	cin >> nEnl;
	for(int i = 0; i < nEnl; i++){
		int vert1, vert2, valor;
		cin >> vert1 >> vert2 >> valor;
		AristaDirigida<int> arista(vert1 - 1, vert2 - 1, valor);

		grafo.ponArista(arista);
	}
	Dijkstra<int> dijkstra(grafo, 0, tiempos_carga);
	if (dijkstra.hayCamino(nPag - 1)){
		cout << dijkstra.distancia(nPag - 1);
	}
	else
		cout << "IMPOSIBLE";

	cout << endl;

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
