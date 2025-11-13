
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

struct Edificio {
	int init;
	int fin;

	bool operator>(const Edificio &e1) const{
		return this->fin > e1.fin;
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;
	if (N == CENTINELA)  // fin de la entrada
		return false;

	priority_queue<Edificio, vector<Edificio>, greater<Edificio>> q;

	for (int i = 0; i < N; i++) {
		int init, fin;
		cin >> init >> fin;

		q.push({ init, fin });
	}
	// resolver el caso posiblemente llamando a otras funciones
	int res = 0;
	int aux = 0;
	while (!q.empty()) {
		if (q.top().init >= aux) {
			aux = q.top().fin;
			res++;
		}
		q.pop();
	}
	// escribir la solución
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
