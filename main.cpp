
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <math.h>
#include <tuple>


using namespace std;

#include "BinTree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename T>
tuple<int, T, T> solveCase(const BinTree<T>& tree, bool& cumple) {
	if (tree.empty()) {
		return { 0, T(), T() };
	}
	T maximo;
	T minimo;

	if (tree.left().empty() && tree.right().empty()) {
		maximo = tree.root();
		minimo = tree.root();
	}

	tuple<int, T, T> left = solveCase(tree.left(), cumple);
	tuple<int, T, T> right = solveCase(tree.right(), cumple);

	// Comprobar balanceo
	if (abs(get<0>(left) - get<0>(right)) > 1) {
		cumple = false;
	}

	// Comprobar orden BST
	if (!tree.left().empty() && tree.root() < get<1>(left)) {
		cumple = false;
	}
	if (!tree.right().empty() && tree.root() > get<2>(right)) {
		cumple = false;
	}
	
	if (tree.root() > get<1>(left) || tree.root() > get<1>(right)) {
		maximo = tree.root();
	}
	else maximo = max(get<1>(left), get<1>(right));

	if (tree.root() < get<2>(left) || tree.root() < get<2>(right)) {
		minimo = tree.root();
	}
	else minimo = min(get<2>(left), get<2>(right));

	return { max(get<0>(left), get<0>(right)) + 1, maximo, minimo};
}

bool resuelveCaso() {
	// leer los datos de la entrada
	string tipe;
	cin >> tipe;

	if (!std::cin)  // fin de la entrada
		return false;

	bool res = true;

	// resolver el caso posiblemente llamando a otras funciones
	if (tipe == "N") {
		BinTree<int> tree;
		tree = read_tree<int>(cin);
		solveCase<int>(tree, res);
	}
	else if (tipe == "P") {
		BinTree<string> tree;
		tree = read_tree<string>(cin);
		solveCase<string>(tree, res);
	}


	// escribir la solución
	res ? cout << "SI\n" : cout << "NO\n";

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
