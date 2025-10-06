
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernández F29 y Jorge Pérez Ramírez F32
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>


using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminoMasCorto {
public:
	using Camino = deque<int>;
	CaminoMasCorto(Grafo const& g, int s) : visit(g.V(), false),
		ant(g.V()), dist(g.V()), s(s) {
		bfs(g);
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}
		// número de aristas entre s y v
		int distancia(int v) const {
		return dist[v];
	}
	// devuelve el camino más corto desde el origen a v (si existe)
	Camino camino(int v) const {
		if (!hayCamino(v)) throw std::domain_error("No existe camino");
		Camino cam;
		for (int x = v; x != s; x = ant[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}
private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
	std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto
	int s;
		void bfs(Grafo const& g) {
		std::queue<int> q;
		dist[s] = 0; visit[s] = true;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w]) {
					ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
					q.push(w);
				}
			}
		}
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int P;

	cin >> P;
	if (!std::cin)  // fin de la entrada
		return false;
	// resolver el caso posiblemente llamando a otras funciones
	unordered_map<string, int> peliculas;
	unordered_map<string, int> actores;
	queue<pair<string, string>> aristas;
	int nVert = 0;
	for (int i = 0; i < P; i++) {
		string pelicula;
		int A;
		cin >> pelicula >> A;
		peliculas.insert({ pelicula, nVert });
		nVert++;
		for (int j = 0; j < A; j++) {
			string actor;
			cin >> actor;
			if (actores.count(actor) == 0) {
				actores.insert({ actor , nVert});
				nVert++;
			}
			aristas.push({pelicula, actor});
		}
	}

	Grafo g(nVert);
	while (!aristas.empty()) {
		g.ponArista(peliculas.at(aristas.front().first), actores.at(aristas.front().second));
		aristas.pop();
	}
	// escribir la solución
	
	int nActores;
	cin >> nActores;
	if (actores.count("KevinBacon") == 1) {
		CaminoMasCorto camino(g, actores.at("KevinBacon"));
		for (int i = 0; i < nActores; i++) {
			string actor;
			cin >> actor;
			cout << actor << " ";
			
			if (actor == "KevinBacon") { cout << 0 << "\n"; }
			else{
				camino.distancia(actores.at(actor)) / 2 == 0 ? cout << "INF\n" : cout << camino.distancia(actores.at(actor)) / 2 << "\n";
			}
		}
	}
	else {
		for (int i = 0; i < nActores; i++) {
			string actor;
			cin >> actor;
			cout << actor << " INF\n";
		}
	}
	
	cout << "---\n";
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

