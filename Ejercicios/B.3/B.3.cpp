
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
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

int rellenarMatriz(Matriz<int>& matriz, const vector<int>& comidas, int cubI, int cubD ) {
	if (matriz[cubI][cubD] == -1) {
		if (cubI == cubD) 
			matriz.at(cubI, cubD) = comidas.at(cubI - 1);
		
		else if (cubI > cubD) 
			matriz.at(cubI, cubD) = 0;
			
		else {
			int aux1 = cubI + 1;
 			int aux2 = cubD;
			if (comidas.at(aux1 - 1) > comidas.at(aux2 - 1))
				aux1++;
			else
				aux2--;
			int izq = rellenarMatriz(matriz, comidas, aux1, aux2) + comidas.at(cubI - 1);

			aux1 = cubI;
			aux2 = cubD - 1;
			if (comidas.at(aux1 - 1) > comidas.at(aux2 - 1))
				aux1++;
			else
				aux2--;
			int der = rellenarMatriz(matriz, comidas, aux1, aux2) + comidas.at(cubD - 1);

			matriz.at(cubI, cubD) = max(izq, der);
		}
	}
	return matriz[cubI][cubD];

}

bool resuelveCaso() {
	// leer los datos de la entrada
	int cubos;

	cin >> cubos;
	if (cubos == 0)
		return false;


	vector<int> comidas(cubos);
	for (int& i : comidas)
			cin >> i;
	
	Matriz<int> matriz(cubos + 1, cubos + 1, -1);
	// escribir la solución

	int sol = rellenarMatriz(matriz, comidas, 1, cubos);

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
