
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernández  F29
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>





class CaminoMasCorto {
public:
    using Camino = deque<int>;
    CaminoMasCorto(Digrafo const& g, int s)
        : visit(g.V(), false), ant(g.V()), dist(g.V()), s(s) {
        bfs(g);
    }

    bool hayCamino(int v) const { return visit[v]; }

    Camino camino(int v) const {
        if (!hayCamino(v)) throw domain_error("No existe camino");
        Camino cam;
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }

private:
    vector<bool> visit;
    vector<int> ant;
    vector<int> dist;
    int s;

    void bfs(Digrafo const& g) {
        queue<int> q;
        dist[s] = 0;
        visit[s] = true;
        q.push(s);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v;
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};


// ================================================================
// Función que resuelve un caso de prueba
// ================================================================

bool resuelveCaso() {
    int NV, NA;
    cin >> NV >> NA;
    if (!cin) return false;

    Digrafo g(NV);
    for (int i = 0; i < NA; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        g.ponArista(v1 - 1, v2 - 1);
    }

    Digrafo gi = g.inverso();  // grafo inverso para rutas hacia el destino

    int consultas;
    cin >> consultas;
    for (int i = 0; i < consultas; i++) {
        int origen, destino;
        cin >> origen >> destino;
        origen--; destino--;

        CaminoMasCorto cOrigen(g, origen);

        if (!cOrigen.hayCamino(destino)) {
            cout << "IMPOSIBLE\n";
            continue;
        }

        CaminoMasCorto cDestino(gi, destino);

        int res = 0;
        for (int i = 0; i < NV; ++i) {
            if (i != origen && i != destino &&
                cOrigen.hayCamino(i) &&
                cDestino.hayCamino(i))
                res++;
        }

        cout << res << "\n";
    }

    cout << "---\n";
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
