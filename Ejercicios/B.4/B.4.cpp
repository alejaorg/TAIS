
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "Grafo.h"
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C, Matriz<int>& A) {
	int V = G.numfils(); // número de vértices de G

	// Inicialización
	C = G;
	A = Matriz<int>(V, V, -1);
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			if (i != j && G[i][j] != Infinito)
				A[i][j] = i;
		}
	}



	// Actualización de matrices
	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				auto temp = C[i][k] + C[k][j];
				if (temp < C[i][j]) {
					C[i][j] = temp;
					A[i][j] = A[k][j];
				}
			}
		}
	}

	// Detección de ciclos negativos
	for (int i = 0; i < V; ++i) {
		if (C[i][i] < 0)
			return false;  // hay un ciclo negativo
	}

	return true; // Todo correcto, sin ciclos negativos
}



bool resuelveCaso() {
	// leer los datos de la entrada
	int numP, numR;
	unordered_map<string, int> personas;
	int index = 0;
	

	cin >> numP >> numR;
	if (!std::cin)  // fin de la entrada
		return false;
	Grafo grafo(numP);
	for (int i = 0; i < numR; i++) {
		string nom1, nom2;
		cin >> nom1 >> nom2;

		if (personas.find(nom1) == personas.end()) {
			personas[nom1] = index++;
		}
		if (personas.find(nom2) == personas.end()) {
			personas[nom2] = index++;
		}

		int u = personas[nom1];
		int v = personas[nom2];
		grafo.ponArista(u,v);
	}

	Matriz<EntInf> grafomatriz(numP, numP); 
	Matriz<EntInf> aux1(numP, numP);
	Matriz<int> aux2(numP, numP);
	for (int i = 0; i < index; i++) {
		for (int a : grafo.ady(i)) {
			grafomatriz[i][a] = 1;
		}
	}

	for (int i = 0; i < numP; i++) {
		for (int j = 0; j < numP; j++) {
			if (grafomatriz[i][j] == 0) grafomatriz[i][j] = Infinito;
		}
	}

	if (!Floyd(grafomatriz, aux1, aux2)) {
		cout << "DESCONECTADA" << "\n";
	}
	else {
		EntInf max = 0;
		for (int i = 0; i < numP; i++) {
			for (int j = i; j < numP; j++) {
				if (j != i && aux1[i][j] > max) max = aux1[i][j];
			}
		}
		if (max != Infinito) {
			cout << max << endl;
		}
		else cout << "DESCONECTADA" << endl;
	}
	// resolver el caso posiblemente llamando a otras funciones

	// escribir la solución

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
