
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernández F29 y Jorge Pérez Ramírez F32
 *@ </authors> */
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase



/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
void dfs(Grafo const& g, int v, vector<bool>& visit, vector<int>& comp, int& tam, int N) {
    visit[v] = true;
    if (v < N) { 
        tam++;
        comp.push_back(v);
    }
    for (int w : g.ady(v)) {
        if (!visit[w]) {
            dfs(g, w, visit, comp, tam, N);
        }
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;
    if (!(cin >> N >> M)) // fin de la entrada
        return false;

    Grafo g(N + M);

    for (int i = 0; i < M; ++i) {
        int nP; cin >> nP;
        for (int j = 0; j < nP; ++j) {
            int p; cin >> p;
            g.ponArista(p - 1, N + i);
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    vector<int> res(N, -1);
    vector<bool> visit(g.V(), false);

    for (int i = 0; i < N; ++i) {
        if (!visit[i]) {
            int tam = 0;
            vector<int> comp;  
            dfs(g, i, visit, comp, tam, N);

            for (int v : comp)
                res[v] = tam;
        }
    }

    for (int x : res)
        cout << x << " ";
    cout << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    cout << "Pulsa Intro para salir...";
    cin.get();
#endif
    return 0;
}
