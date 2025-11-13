
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * 
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

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M;

	cin >> N >> M;
	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<int, vector<int>, less<int>> jugadores;
	priority_queue<int, vector<int>, less<int>> camisetas;
	for (int i = 0; i < N; i++) {
		int aux;
		cin >> aux;
		jugadores.push(aux);
	}

	for (int i = 0; i < M; i++) {
		int aux;
		cin >> aux;
		camisetas.push(aux);
	}

	int res = 0;
	while (!camisetas.empty() && !jugadores.empty()) {
		if (camisetas.top() == jugadores.top() || camisetas.top() == jugadores.top() + 1) {
			jugadores.pop();
			camisetas.pop();
		}
		else if (jugadores.top() < camisetas.top()) {
			camisetas.pop();
		}
		else if (jugadores.top() > camisetas.top()){
			jugadores.pop();
			res++;
		}
	}
	// escribir la solución

	cout << jugadores.size() + res << "\n";

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
