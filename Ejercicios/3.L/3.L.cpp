
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernández F29 y Jorge Pérez Ramírez F32
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct Canal {
	int indice;
	int audiencia;

	bool operator>(const Canal &otro) const{
		return audiencia == otro.audiencia ? indice < otro.indice : audiencia > otro.audiencia;
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int D, C, N;

	cin >> D >> C >> N;
	if (!std::cin)  // fin de la entrada
		return false;

	//vector<int> canales;
	IndexPQ<Canal, greater<Canal>> cola(C + 1);
	IndexPQ<Canal, greater<Canal>> canales(C + 1);
	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < C; i++) {
		Canal aux;
		cin >> aux.audiencia;
		aux.indice = i;
		cola.push(i + 1, aux);
		canales.push(i + 1,{i+1,0});
	}
	int time = 0;
	for (int i = 0; i < N; i++) {
		int act_time, indice;
		cin >> act_time >> indice;
		int top = cola.top().elem;
		canales.update(top, { top, canales.priority(top).audiencia + (act_time - time) });
		while (indice != -1) {
			int share;
			cin >> share;
			Canal aux;
			aux.indice = indice;
			aux.audiencia = share;
			cola.update(indice, aux);
			cin >> indice;
		}
		time = act_time;
	}
	// escribir la solución
	canales.update(cola.top().elem, { cola.top().elem, canales.priority(cola.top().elem).audiencia + (D - time) });
	while (!canales.empty() && canales.top().prioridad.audiencia != 0) {
		cout << canales.top().elem << " " << canales.top().prioridad.audiencia << "\n";
		canales.pop();
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

