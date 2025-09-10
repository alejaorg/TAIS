
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */

void reconstruir(int indice, const vector<int> &solV, const vector<pair<int, int>> &posiciones, int &beneficio){
		beneficio -= posiciones[indice].second;
		if (beneficio == 0) {
			cout << posiciones[indice].first  << " ";
		}
		else {
			int aux1 = indice;
			for (int j = indice - 1; j >= 0; j--) {
				if (beneficio == solV[j]) aux1 = j;
			}
	/*		indice--;
			while (beneficio != solV[indice]) indice--;*/
			reconstruir(aux1, solV, posiciones, beneficio);
			cout << posiciones[indice].first << " ";
		}
}

int sol(const vector<pair<int,int>> &posiciones, vector<int> &solV, const int &dist){
	int res = 0;
	for (int i = 0; i < posiciones.size(); i++) {
		solV[i] = posiciones[i].second; //Caso base (solo se pilla la primera tienda)
		for (int j = i - 1; j >= 0; j--) {
			if ((posiciones[i].first - posiciones[j].first) >= dist) {
				solV[i] = max(solV[i], solV[j] + posiciones[i].second);
			}
		}
		res = solV[i] > solV[res] ? i : res;
	}
	return res;
}

 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int nTiendas, dist;

	cin >> nTiendas >> dist;
	if (!std::cin)  // fin de la entrada
		return false;
	
	vector<pair<int, int>> posiciones(nTiendas);
	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < nTiendas; i++) {
		int pos;
		cin >> pos;
		posiciones[i].first = pos;
	}

	for (int i = 0; i < nTiendas; i++) {
		int beneficio;
		cin >> beneficio;
		posiciones[i].second = beneficio;
	}	// escribir la soluci�n

	vector<int> solV(nTiendas, 0);
	int benef = sol(posiciones, solV, dist);

	cout << solV[benef] << ": ";

	reconstruir(benef, solV, posiciones, solV[benef]);

	cout << endl;
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
