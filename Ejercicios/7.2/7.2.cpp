
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <limits>

using namespace std;

#include "GrafoValorado.h" 
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
	using Camino = deque<Arista<Valor>>;
	Dijkstra(GrafoValorado<Valor> const& g, int orig, vector<int> &contadores) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
		vector<bool> visitados(contadores.size(), false);
		dist[origen] = 0;
		contadores[origen] = 1;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v)){
				relajar(a, contadores, visitados);

			}
			visitados[v] = true;
		}
	}
	
	bool hayCamino(int v) const { return dist[v] != INF; }
	Valor distancia(int v) const { return dist[v]; }
	Camino camino(int v) const {
		Camino cam;
		// recuperamos el camino retrocediendo
		Arista<Valor> a;
		for (a = ulti[v]; a.uno() != origen; a = ulti[a.uno()])
			cam.push_front(a);
		cam.push_front(a);
		return cam;
	}
private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<Arista<Valor>> ulti;
	IndexPQ<Valor> pq;
	void relajar(Arista<Valor> a, vector<int> &conts, vector<bool> visitados) {
		int v = a.uno(), w = a.otro(v);
		if (!visitados[v]) {
			if (dist[w] > dist[v] + a.valor()) {
				dist[w] = dist[v] + a.valor(); ulti[w] = a;
				pq.update(w, dist[w]);
				conts[w] = conts[v];
			}
			else if (dist[w] == dist[v] + a.valor())
				conts[w]++;
		}
	}
};



bool resuelveCaso() {
	// leer los datos de la entrada
	int vert;
	cin >> vert;
	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> grafo(vert);
	int a;
	cin >> a;

	for (int i = 0; i < a; i++){
		int vert1, vert2, valor;
		cin >> vert1 >> vert2 >> valor;
		Arista<int> arista(vert1 - 1, vert2 - 1, valor);
		grafo.ponArista(arista);
	}
	vector<int> conts(vert, 0);

	Dijkstra<int> dijs(grafo, 0, conts);

	/*deque<Arista<int>> cola = dijs.camino(vert-1);
	while (!cola.empty()) {
		cout << cola.front().uno();
		cola.pop_front();
	}*/
	cout << conts[vert - 1] << endl;
	

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
