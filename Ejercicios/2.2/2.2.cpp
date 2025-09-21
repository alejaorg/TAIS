/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

La cola de prioridad guarda elementos con su id y el instante en el que deben ejecutarse.
Siempre se atiende el de menor instante, y en caso de empate gana el id más pequeño.
Cada vez que se atiende un elemento, se reprograma sumando su periodo original.
El coste es O((N + K) log N), pues cada inserción y extracción de la cola cuesta O(log N).

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
 //@ <answer>
const int CENTINELA = 0;

struct Elem {
    int id;
    int periodo;
    int siguiente; 
};

struct Comparator {
    bool operator()(Elem const& a, Elem const& b) const {
        if (a.siguiente == b.siguiente)
            return a.id < b.id;          
        else
            return a.siguiente < b.siguiente; 
    }
};

bool resuelveCaso() {
    int N, K;
    cin >> N;
    if (N == CENTINELA) return false;

    vector<int> periodos(N); 
    IndexPQ<Elem, Comparator> cola(N);

    for (int i = 0; i < N; i++) {
        int id, periodo;
        cin >> id >> periodo;
        periodos[i] = periodo;
        Elem e{ id, periodo, periodo };
        cola.push(i, e); 
    }

    cin >> K;

    while (K-- > 0) {
        int idx = cola.top().elem;      
        Elem e = cola.top().prioridad;  
        cout << e.id << "\n";
        cola.pop();
        e.siguiente += periodos[idx];
        cola.push(idx, e);
    }
    cout << "---\n";
    return true;
}

//@ </answer>

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    if (!in.is_open())
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
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
