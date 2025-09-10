#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include "GrafoValorado.h"
#include "IndexPQ.h"

using namespace std;

template <typename Valor>
class DijkstraMultiFuente {
public:
    DijkstraMultiFuente(GrafoValorado<Valor> const& g, vector<int> const& origenes) :
        dist(g.V(), INF), pq(g.V()) {

        for (int origen : origenes) {
            dist[origen] = 0;
            pq.push(origen, 0);
        }

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();

            for (auto const& arista : g.ady(v)) {
                int w = arista.otro(v);
                Valor nueva = dist[v] + arista.valor();
                if (dist[w] > nueva) {
                    dist[w] = nueva;
                    pq.update(w, nueva);
                }
            }
        }
    }

    Valor distancia(int v) const { return dist[v]; }

private:
    const Valor INF = numeric_limits<Valor>::max();
    vector<Valor> dist;
    IndexPQ<Valor> pq;
};

bool resuelveCaso() {
    int D, P, C;
    cin >> D >> P >> C;
    if (!cin) return false;

    GrafoValorado<int> grafo(P);
    for (int i = 0; i < C; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        grafo.ponArista(Arista<int>(u - 1, v - 1, t));
    }

    int B;
    cin >> B;
    vector<int> borriquines(B);
    for (int i = 0; i < B; ++i) {
        cin >> borriquines[i];
        borriquines[i]--;  // convertir a 0-based
    }

    DijkstraMultiFuente<int> dijkstra(grafo, borriquines);
    int contador = 0;
    for (int i = 0; i < P; ++i) {
        if (dijkstra.distancia(i) <= D) ++contador;
    }

    cout << contador << '\n';
    return true;
}

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
