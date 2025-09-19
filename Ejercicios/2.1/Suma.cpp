
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;


using lli = long long int;
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
 lli esfuerzo(priority_queue<lli, vector<lli>, greater<lli>> & pq) {
	lli sol = 0, sum1, sum2;
	while (pq.size() != 1) {
		lli acum;
		sum1 = pq.top();
		pq.pop();
		sum2 = pq.top();
		pq.pop();
		acum = sum1 + sum2;
		pq.push(acum);
		sol += acum;
	}
	return sol;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;
	if (N == 0)
		return false;

	priority_queue<lli, vector<lli>, greater<lli>> pq;
	lli num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		pq.push(num);
	}
	cout << esfuerzo(pq) << '\n';
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
