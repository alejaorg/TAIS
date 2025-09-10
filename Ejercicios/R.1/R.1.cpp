#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <limits>

using namespace std;

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "Grafo.h"
#include "PriorityQueue.h"


class CaminosDFS {
private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant;
    // ant[v] = último vértice antes de llegar a v
    int s;
    // vértice origen
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


template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;
public:
    Valor costeARM() const {
        return coste;
    }
    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0) {
    PriorityQueue<Arista<Valor>> pq(g.aristas());
    ConjuntosDisjuntos cjtos(g.V());
    while (!pq.empty()) {
        auto a = pq.top(); pq.pop();
        int v = a.uno(), w = a.otro(v);
        if (!cjtos.unidos(v, w)) {
            cjtos.unir(v, w);
            _ARM.push_back(a); coste += a.valor();
            if (_ARM.size() == g.V() - 1) break;
        }
    }
}
};


bool resuelveCaso() {
    int vert, arist;
    cin >> vert >> arist;
    if (!cin) return false;

    GrafoValorado<int> grafo(vert);
    for (int i = 0; i < arist; i++) {
        int vert1, vert2, valor;
        cin >> vert1 >> vert2 >> valor;
        grafo.ponArista({ vert1 - 1, vert2 - 1, valor });
    }

    int org, tesoro;
    cin >> org >> tesoro;

    ARM_Kruskal<int> krus(grafo);
    Grafo graf(vert);
    for (Arista<int> i : krus.ARM()) {
        graf.ponArista(i.uno(), i.otro(i.uno()));
    }
    CaminosDFS dfs(graf, org - 1);
    
    if (dfs.hayCamino(tesoro - 1)) {
        int max = 0;
        if (graf.A() != 0) {
            deque<int> cola = dfs.camino(tesoro - 1);
    
            int vert_aux = cola.front();
            cola.pop_front();
            while (!cola.empty()) {
                int i = 0;
                vector<Arista<int>> adyacentes = grafo.ady(vert_aux);
                while (i < adyacentes.size() && adyacentes[i].otro(vert_aux) != cola.front()) {
                    i++;
                }
                if (max < adyacentes[i].valor()) max = adyacentes[i].valor();
                vert_aux = cola.front();
                cola.pop_front();
            }
        }
        cout << max << endl;
    }
    else cout << "IMPOSIBLE" << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open()) {
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
        return 1;
    }
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    cout << "Pulsa Intro para salir..." << flush;
    cin.get();
#endif
    return 0;
}
