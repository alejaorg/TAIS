
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>


using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminosDFS {
private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	std::vector<int> ant;
	// ant[v] = último vértice antes de llegar a v
	int s;
	// vértice origen
	void dfs(GrafoValorado<int> const& G, int v, int umbral) {
		visit[v] = true;
		for (auto a : G.ady(v)) {
			if (a.valor() >= umbral) {
				int w = a.otro(v);
				if (!visit[w])
					dfs(G, w, umbral);
			}
		}
	}
public:
	CaminosDFS(GrafoValorado<int> const& g, int s, int umbral) : visit(g.V(), false),
		ant(g.V()), s(s) {
		dfs(g, s, umbral);
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}
		using Camino = std::deque<int>; // para representar caminos
	// devuelve un camino desde el origen a v (debe existir)
	Camino camino(int v) const {
		if (!hayCamino(v))
			throw std::domain_error("No existe camino");
		Camino cam;
		// recuperamos el camino retrocediendo
		for (int x = v; x != s; x = ant[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int vert, arist;

	cin >> vert >> arist;
	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> grafo(vert);
	for (int i = 0; i < arist; i++) {
		int vert1, vert2, valor;
		cin >> vert1 >> vert2 >> valor;
		Arista<int> arista(vert1 - 1, vert2 - 1, valor);
		grafo.ponArista(arista);
	}
	// resolver el caso posiblemente llamando a otras funciones

	int k;
	cin >> k;

	for(int i = 0; i < k; i++){
		int vert1, vert2, umbral;
		cin >> vert1 >> vert2 >> umbral;
		CaminosDFS caminoDFS(grafo, vert1 - 1, umbral);
		if (caminoDFS.hayCamino(vert2 - 1)) cout << "SI";
		else cout << "NO";			   
		cout << endl;
	}
	
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
