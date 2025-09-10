
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>
struct Pelicula {
	int init;
	int fin;
	int tiempo;
};


int sol(const vector<Pelicula>& pelis, vector<int>& sol) {
	int res = 0;
	for (int i = 0; i < pelis.size(); i++) {
		sol[i] = pelis[i].tiempo;  // caso base: ver solo esta pel�cula
		for (int j = i - 1; j >= 0; j--) {
			if (pelis[i].init >= pelis[j].fin + 10) {
				sol[i] = max(sol[i], pelis[i].tiempo + sol[j]);
			}
		}
		res = max(res, sol[i]);
	}
	return res;
}


bool resuelveCaso() {
	// leer los datos de la entrada
	int numP;

	cin >> numP;
	if (numP == 0)
		return false;
	// resolver el caso posiblemente llamando a otras funciones
	vector<Pelicula> lista(numP);
	for (int i = 0; i < numP; i++) {
		Pelicula peli;
		int aux1, aux2, time;
		char puntos;
		cin >> aux1 >> puntos >> aux2 >> time;
		peli.init = aux1 * 60 + aux2;
		peli.tiempo = time;
		peli.fin = peli.init + time;
		lista[i] = peli;
	}
	// escribir la soluci�n
	sort(lista.begin(), lista.end(), [](const Pelicula & pel1, const Pelicula & pel2) {
		return pel1.fin < pel2.fin;
	});
	vector<int> solv(numP);

	cout << sol(lista, solv) << endl;

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
