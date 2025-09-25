
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (FXX) de los autores de la soluci�n.
 *
 * Alejandro Orgaz Fernandez F29
 * Jorge Perez Ramirez F32
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

// propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>
struct tGrupo {
	int intrumentos;
	int partituras = 1;

	int calcularFactor() {
		if (intrumentos % partituras == 0) {
			return intrumentos / partituras;
		}
		else {
			return (intrumentos / partituras) + 1;
		}
	}
};

struct Comparator {
	bool operator()(tGrupo e1, tGrupo e2) {
		return e1.calcularFactor() < e2.calcularFactor();
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int p, n;

	cin >> p >> n;
	if (!std::cin)  // fin de la entrada
		return false;

	priority_queue<tGrupo, vector<tGrupo>, Comparator> cola;
	for (int i = 0; i < n; i++) {
		tGrupo aux;
		cin >> aux.intrumentos;
		cola.push(aux);
	}
	// resolver el caso posiblemente llamando a otras funciones
	p -= n;
	while (p > 0) {
		tGrupo aux = cola.top();
		cola.pop();
		aux.partituras++;
		cola.push(aux);
		p--;
	}
	// escribir la soluci�n
	tGrupo res = cola.top();
	cout << res.calcularFactor() << endl;

	return true;
}
/*
bool resuelveCaso() {
	// leer los datos de la entrada
	int p, n;

	cin >> p >> n;
	if (!std::cin)  // fin de la entrada
		return false;

	priority_queue<int, vector<int>, less<int>> cola;
	for (int i = 0; i < n; i++) {
		int aux;
		cin >> aux;
		cola.push(aux);
	}
	// resolver el caso posiblemente llamando a otras funciones
	p -= n;
	while (p > 0) {
		int aux = cola.top();
		cola.pop();
		if (aux % 2 != 0) {
			cola.push((aux + 1) / 2);
			cola.push((aux - 1) / 2);
		}
		else {
			cola.push(aux / 2);
			cola.push(aux / 2);
		}
		p--;
	}
	// escribir la soluci�n

	cout << cola.top() << endl;

	return true;
}*/

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
