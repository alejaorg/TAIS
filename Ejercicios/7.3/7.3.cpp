
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

using namespace std;

#include "DigrafoValorado.h" 
#include "IndexPQ.h"// propios o los de las estructuras de datos de clase

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
    using Camino = deque<Valor>;

    Dijkstra(DigrafoValorado<Valor> const& g, int orig)
        : origen(orig),
        dist(g.V(), INF),
        ulti(g.V()),
        pq(g.V()),
        num_d(g.V(), 0),
        visitado(g.V(), false) {

        dist[origen] = 0;
        num_d[origen] = 1;
        pq.push(origen, 0);

        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();

            if (visitado[v]) continue;
            visitado[v] = true;

            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    int getNumD(int v) const { return num_d[v]; }

private:
    const Valor INF = std::numeric_limits<Valor>::max() / 2;
    int origen;
    std::vector<Valor> dist;
    std::vector<int> num_d;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    std::vector<bool> visitado;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        Valor peso = a.valor();

        if (dist[w] > dist[v] + peso) {
            dist[w] = dist[v] + peso;
            ulti[w] = a;
            pq.update(w, dist[w]);
            num_d[w] = num_d[v];  
        }
        else if (dist[w] == dist[v] + peso) {
            num_d[w] += num_d[v]; 
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

	Dijkstra<int> ds(g, 0);

	// escribir la solución
	cout << ds.getNumD(N - 1) << "\n";
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
