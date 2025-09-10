/*@ <authors>
 *
 * Nombre, Apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

/*@ <answer>

 Esta solución usa programación dinámica para calcular el coste mínimo de una instalación
 de bombillas con potencia total entre PMin y PMax. Se modela como un problema similar
 al cambio de moneda ilimitado (unbounded knapsack), donde:

 - Filas: tipos de bombillas.
 - Columnas: potencias desde 0 hasta PMax.
 - dp[i][j]: coste mínimo para conseguir potencia j usando bombillas 0..i.

Se calcula para cada potencia y tipo la mejor combinación de bombillas.
Finalmente se busca el mínimo coste entre potencias válidas.

Complejidad: O(N * PMax), siendo N el número de tipos y PMax la potencia máxima.

@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
	int N, PMax, PMin;
	if (!(cin >> N >> PMax >> PMin)) return false;

	vector<int> potencias(N);
	vector<int> costes(N);

	for (int i = 0; i < N; ++i) cin >> potencias[i];
	for (int i = 0; i < N; ++i) cin >> costes[i];

	const int INF = INT_MAX;
	vector<vector<int>> dp(N, vector<int>(PMax + 1, INF));

	// Caso base: potencia 0 sin coste
	for (int i = 0; i < N; ++i)
		dp[i][0] = 0;

	// Primera fila: usando solo la bombilla 0 (unbounded)
	for (int j = potencias[0]; j <= PMax; ++j) {
		if (dp[0][j - potencias[0]] != INF)
			dp[0][j] = dp[0][j - potencias[0]] + costes[0];
	}

	// Rellenar resto de filas
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j <= PMax; ++j) {
			// No usar la bombilla i
			dp[i][j] = dp[i - 1][j];

			// Usar al menos una bombilla i
			if (j - potencias[i] >= 0 && dp[i][j - potencias[i]] != INF) {
				int nuevo_coste = dp[i][j - potencias[i]] + costes[i];
				if (nuevo_coste < dp[i][j])
					dp[i][j] = nuevo_coste;
			}
		}
	}

	// Buscar coste mínimo entre PMin y PMax
	int coste_min = INF;
	int potencia_opt = -1;
	for (int p = PMin; p <= PMax; ++p) {
		if (dp[N - 1][p] < coste_min) {
			coste_min = dp[N - 1][p];
			potencia_opt = p;
		}
	}

	if (coste_min == INF) cout << "IMPOSIBLE\n";
	else cout << coste_min << " " << potencia_opt << "\n";

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