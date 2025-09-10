
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <limits>

using namespace std;



using namespace std;

bool resuelveCaso() {
	int N, L;
	cin >> N >> L;
	if (!cin) return false;

	vector<int> longitudes(N), costes(N);
	for (int i = 0; i < N; ++i) {
		cin >> longitudes[i] >> costes[i];
	}

	const long long INF = 1e18;
	vector<long long> formas(L + 1, 0);
	vector<int> minCuerdas(L + 1, 1e9);
	vector<long long> minCoste(L + 1, INF);

	formas[0] = 1;
	minCuerdas[0] = 0;
	minCoste[0] = 0;

	for (int i = 0; i < N; ++i) {
		int len = longitudes[i], cost = costes[i];
		for (int j = L; j >= len; --j) {
			if (formas[j - len] > 0) {
				formas[j] += formas[j - len];

				minCuerdas[j] = min(minCuerdas[j], minCuerdas[j - len] + 1);
				minCoste[j] = min(minCoste[j], minCoste[j - len] + cost);
			}
		}
	}

	if (formas[L] == 0)
		cout << "NO\n";
	else
		cout << "SI " << formas[L] << " " << minCuerdas[L] << " " << minCoste[L] << "\n";

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
