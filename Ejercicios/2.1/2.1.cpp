
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */

const int CENTINELA = 0;
 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;
	if (N == CENTINELA)
		return false;

	priority_queue<long long int, vector<long long int>, greater<long long int>> cola;
	for (int i = 0; i < N; i++) {
		int aux;
		cin >> aux;
		cola.push(aux);
	}
	// resolver el caso posiblemente llamando a otras funciones
	long long int acum = cola.top();
	cola.pop();
	long long int res = 0;
		while (!cola.empty()) {
			long long int elem = cola.top(); 
			elem += acum;
			cola.pop(); 
			cola.push(elem); 
			res += elem;
			acum = cola.top(); 
			cola.pop(); 
		}
	// escribir la soluci�n

	cout << res << endl;

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
