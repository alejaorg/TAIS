
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 * JORGE PEREZ RAMIREZ F32
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

struct tPaciente {
	string nom;
	int prio, turno;
};

struct comparador {
	bool operator()(tPaciente const& a, tPaciente const& b) const {
		if (a.prio == b.prio)
			return a.turno < b.turno;
		return a.prio > b.prio;
	}
};
/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada

	int eventos;
	cin >> eventos;

	if (eventos == 0)
		return false;

	PriorityQueue<tPaciente, comparador> cola;
	for(int i = 0; i < eventos; ++i){
		char tipo;
		cin >> tipo;
		if(tipo == 'I'){
			string nom;
			int prioridad;

			cin >> nom >> prioridad;
			cola.push({ nom, prioridad, i });
		}
		else if(tipo == 'A'){
			cout << cola.top().nom  << '\n';
			cola.pop();
		}
		
	}

	cout << "---" << '\n';
	// resolver el caso posiblemente llamando a otras funciones

	// escribir la soluci�n

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
