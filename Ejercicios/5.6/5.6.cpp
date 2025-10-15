/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernández F29 Jorge Pérez Ramírez F32
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;



/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct tNodo {
	bool visitado;
	int dist, conecta;
};

bool resuelveCaso() {
	// leer los datos de la entrada

	int N, K, S, E;

	cin >> N >> K >> S >> E;

	if (N == 0 && K == 0 && S == 0 && E == 0)  // fin de la entrada
		return false;

	int meta = N * N;
	vector<tNodo> g(meta + 1);
	int cont = 0;

	for (tNodo& a : g) { //En el peor de los casos 10000 iteraciones
		a = { false, 0, cont };
		cont++;
	}
	

	for (int i = 0; i < S + E; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		g[v1].conecta = v2;
	}

	//CaminoMasCorto camino(g, S, T, opers, res);
	queue<int> q;
	int res = 0;

	g[1].visitado = true;
	if (g[1].conecta != meta) {
		q.push(g[1].conecta);

		while (!q.empty() && res == 0) {
			int v = q.front(); q.pop();
			int aux = v;
			if (g[aux].conecta == meta)
				res = g[aux].dist;
			else {
				for (int i = 1; i <= K && v+i <= meta; i++) {
					aux = g[v + i].conecta;
					if (!g[aux].visitado) {
						g[aux].dist = g[v].dist + 1; g[aux].visitado = true;
						q.push(aux);
					}
				}
			}
		}

	}
	cout << res << "\n";
	// resolver el caso posiblemente llamando a otras funciones

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
