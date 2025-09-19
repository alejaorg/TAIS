
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


using lli = long long int;
/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
	// escribir la soluci�n

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
