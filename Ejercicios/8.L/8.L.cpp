
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
const int CENTINELA = 0;

struct Event
{
	int init;
	int fin;
	int indice;

	bool operator>(const Event &other) const {
		return fin == other.fin ? init > other.init : fin > other.fin;
	}
};

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0) return false;

    vector<Event> eventos(N);
    for (int i = 0; i < N; ++i)
        cin >> eventos[i].init >> eventos[i].fin, eventos[i].indice = i;

    sort(eventos.begin(), eventos.end(), [](const Event& a, const Event& b) {
        return a.init < b.init;
        });

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> salaDeEvento(N);
    int numSalas = 0;

    for (auto& e : eventos) {
        if (!pq.empty() && pq.top().first <= e.init) {
            int sala = pq.top().second;
            pq.pop();
            salaDeEvento[e.indice] = sala;
            pq.push({ e.fin, sala });
        }
        else {
            numSalas++;
            salaDeEvento[e.indice] = numSalas;
            pq.push({ e.fin, numSalas });
        }
    }
    cout << numSalas << "\n";
    for (int i = 0; i < N; ++i)
        cout << salaDeEvento[i] << " ";
    cout << "\n";

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
	std::cout << "pair<int, int>ulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
