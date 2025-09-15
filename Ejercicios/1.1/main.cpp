
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <tuple>
#include <cmath>
#include <unordered_set>


using namespace std;

#include "BinTree.h"  

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
tuple<int, T, T> solveCase(const BinTree<T>& tree, bool& cumple, unordered_set<T> &elems) {
	if (!tree.empty()) {
		if (tree.left().empty() && tree.right().empty()) {
			elems.insert(tree.root());
			return { 1, tree.root(), tree.root() };
		}
		else {
			//if (cumple) {
				

				tuple<int, T, T> der = { 0, tree.root(), tree.root() };

				bool cder = true;
				if (!tree.right().empty()) {
					der = solveCase(tree.right(), cumple, elems);
					cder = tree.root() < get<1>(der);
				}
				else {
					cder = true;
				}

				bool cizq = true;
				tuple<int, T, T> izq = { 0, tree.root(), tree.root() };
				if (!tree.left().empty()) {
					izq = solveCase(tree.left(), cumple, elems);
					cizq = tree.root() > get<2>(izq);
				}
				else {
					cizq = true;
				}

				if (cumple)
					cumple = (abs(get<0>(der) - get<0>(izq)) <= 1) && cder && cizq && elems.count(tree.root()) == 0;
				//if (get<0>(der) == -1) der = izq;
				//if (get<0>(izq) == -1) izq = { 0, tree.root(), tree.root() };

				elems.insert(tree.root());

				return { max(get<0>(der), get<0>(izq)) + 1, min(tree.root(), get<1>(izq)), max(tree.root(), get<2>(der)) };

			//}
			//else {
			//	return { 0, tree.root(), tree.root() };
			//}

		}
	}
	else { return { 0, T(), T() };
	}
}


bool resuelveCaso() {
	
	string tipe;
	cin >> tipe;

	if (!std::cin)  
		return false;

	bool res = true;

	
	if (tipe == "N") {
		BinTree<int> tree;
		unordered_set<int> elems;
		tree = read_tree<int>(cin);
		solveCase<int>(tree, res, elems);
	}
	else if (tipe == "P") {
		BinTree<string> tree;
		unordered_set<string> elems;
		tree = read_tree<string>(cin);
		solveCase<string>(tree, res, elems);
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
