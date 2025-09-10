
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <math.h>
#include <tuple>


using namespace std;

#include "BinTree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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


	// escribir la soluci�n
	res ? cout << "SI\n" : cout << "NO\n";

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
