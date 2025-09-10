
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int rellenarMatriz(Matriz<int>& matriz, vector<string> lista1, vector<string> lista2, int i, int j/*, vector<int>& sol*/) {
	if (matriz.at(i, j) == -1) {
		if (i == lista1.size() || j == lista2.size())
			matriz.at(i, j) = 0;
		else if (i > lista1.size() || j > lista2.size())
			return -7;

		else {
			int sol;
			int vAux1 = rellenarMatriz(matriz, lista1, lista2, i + 1, j/*, /vAux1*/);
			string canc1 = lista1.at(i);

			bool encontrado = false;
			while (j < lista2.size() && !encontrado) {
				if (canc1 == lista2.at(j))
					encontrado = true;
				else
					j++;
			}

			if (encontrado) {
				int vAux2;
				//vAux2.push_back(i);
				vAux2 = rellenarMatriz(matriz, lista1, lista2, i + 1, j + 1/*, vAux2*/) + 1;

				if (vAux1 >= vAux2)
					sol = vAux1;
				else
					sol = vAux2;
			}
			else
				sol = vAux1;

			matriz.at(i, j) = sol;

		}

	}
	return matriz.at(i, j);
}


bool resuelveCaso() {
	// leer los datos de la entrada
	vector<string> canciones1, canciones2;
	string aux;

	for (int i = 0; i < 2; i++) {
		std::getline(std::cin, aux);
		if (!std::cin)  // fin de la entrada
			return false;
		std::istringstream iss(aux);
		std::string palabra;
		// Leer palabra por palabra desde la línea
		while (iss >> palabra) {
			i == 0 ? canciones1.push_back(palabra) : canciones2.push_back(palabra);
		}

	}
	// resolver el caso posiblemente llamando a otras funciones

	Matriz<int> matriz((int)canciones1.size() + 1, (int)canciones2.size() + 1, -1);

	vector<int> solR;

	int sol = rellenarMatriz(matriz, canciones1, canciones2, 0, 0);
	// escribir la solución
	cout << matriz << "\n";
	cout << sol << "\n";

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
