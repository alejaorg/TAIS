
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernandez F29
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Ordenamos en un priority_queue atacantes y defensores enntonces comparamos el primer defensor con el primer atacante de sus respectivas listas
 si el defensor puede con ese atacante eleminamos al atacante y en cualquier caso eliminamos el defensor dado que si puede con el atacante ese grupo 
 estará ocupado y si no puede con el defensor mas devil no podrá con ninguno otro por lo tanto es inutil y esto funciona a que al ordenar de menor 
 a mayor lo que hacemos es buscar el defensor mas debil capaz de vencer al atacante mas fuerte entonces los atacantes qu equeden en su cola son los 
 que no podremos defender por lo tanto el nº de ciudades menos los atacantes sin defender seran las ciudades defendidas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<int, vector<int>, greater<int>> atacantes;
	priority_queue<int, vector<int>, greater<int>> defensores;
	for (int i = 0; i < N; i++) {
		int atq;
		cin >> atq;
		atacantes.push(atq);
	}
	for (int i = 0; i < N; i++) {
		int def;
		cin >> def;
		defensores.push(def);
	}

	while (!defensores.empty()) {
		if (defensores.top() >= atacantes.top()) {
			atacantes.pop();
		}
		defensores.pop();
	}

	// escribir la solución
	cout << N - atacantes.size() << "\n";

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
