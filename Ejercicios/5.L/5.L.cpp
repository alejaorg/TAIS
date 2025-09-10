#include <iostream>
#include <fstream>
#include <deque>
#include <vector>

using namespace std;

#include "Digrafo.h"  // Asegúrate de que tienes esta clase implementada

// ---------------------
// Clase para DFS clásico
// ---------------------
class DFSDirigido {
public:
    DFSDirigido(Digrafo const& g, int s) : visit(g.V(), false) {
        dfs(g, s);
    }
    bool alcanzable(int v) const {
        return visit[v];
    }
private:
    std::vector<bool> visit;
    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        for (int w : g.ady(v))
            if (!visit[w]) dfs(g, w);
    }
};

// ---------------------------
// Detección de ciclos dirigidos
// ---------------------------
class CicloDirigido {
public:
    using Camino = deque<int>;

    CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
        apilado(g.V(), false), hayciclo(false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }

    bool hayCiclo() const { return hayciclo; }

private:
    std::vector<bool> visit;
    std::vector<int>  ant;
    std::vector<bool> apilado;
    bool hayciclo;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (hayciclo) return;
            if (!visit[w]) {
                ant[w] = v; dfs(g, w);
            }
            else if (apilado[w]) {
                hayciclo = true;
                return;
            }
        }
        apilado[v] = false;
    }
};

// ---------------------------
// Resolución de un caso
// ---------------------------
bool resuelveCaso() {
    int n;
    cin >> n;
    if (!cin) return false;

    Digrafo grafo(n + 1);
    for (int i = 0; i < n; ++i) {
        char ins;
        cin >> ins;
        if (ins == 'A') {
            grafo.ponArista(i, i + 1);
        }
        else {
            int valor;
            cin >> valor;
            grafo.ponArista(i, valor - 1);
            if (ins == 'C') {
                grafo.ponArista(i, i + 1);
            }
        }
    }

    DFSDirigido dfsDesde0(grafo, 0);

    Digrafo grafoReducido(grafo.V());
    for (int v = 0; v < grafo.V(); ++v) {
        if (dfsDesde0.alcanzable(v)) {
            for (int w : grafo.ady(v)) {
                if (dfsDesde0.alcanzable(w)) {
                    grafoReducido.ponArista(v, w);
                }
            }
        }
    }

    CicloDirigido ciclo(grafoReducido);

    if (!ciclo.hayCiclo()) {
        cout << "SIEMPRE" << endl;
    }
    else {
        if (dfsDesde0.alcanzable(n)) {
            cout << "A VECES" << endl;
        }
        else {
            cout << "NUNCA" << endl;
        }
    }

    return true;
}

// ---------------------------
// Programa principal
// ---------------------------
int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    if (!in.is_open()) {
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
        return 1;
    }
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}
