
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "StringIPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */

struct tPais {
	string nom;
	int puntos;
};

struct Comparator {
	bool operator()(tPais const& e1, tPais const& e2) {
		return e1.puntos == e2.puntos ? e1.nom < e2.nom : e1.puntos > e2.puntos;
	}
};

 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	IndexPQ<string, tPais, Comparator> cola;

	for (int i = 0; i < N; i++) {
		string pais;
		cin >> pais;
		if (pais == "?") {
			cout << cola.top().elem << " " << cola.top().prioridad.puntos << "\n";
		}
		else {
			int puntos;
			cin >> puntos;
			if (cola.estaElem(pais)) 
				cola.update(pais, { pais, cola.priority(pais).puntos + puntos });
			else
				cola.push(pais, { pais, puntos });
		}
	}
	// resolver el caso posiblemente llamando a otras funciones
	cout << "---" << "\n";
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
