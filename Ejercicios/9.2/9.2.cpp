
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
#include <algorithm>

using namespace std;

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
struct Inter {
	int init;
	int fin;


};


bool resuelveCaso() {
    int C, F, N;
    cin >> C >> F >> N;
    if (C == 0 && F == 0 && N == 0) return false;

    vector<Inter> v;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        if (b >= C && a < F) { 
            v.push_back({ a, b });
        }
    }

    sort(v.begin(), v.end(), [](const Inter& x, const Inter& y) {
        if (x.init == y.init) return x.fin > y.fin;
        return x.init < y.init;
        });

    int res = 0;
    int covered = C;
    int i = 0;
    while (covered < F) {
        int best = covered;
        while (i < v.size() && v[i].init <= covered) {
            best = max(best, v[i].fin);
            i++;
        }
        if (best == covered) {
            cout << "Imposible\n";
            return true;
        }
        covered = best;
        res++;
    }

    cout << res << "\n";
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
