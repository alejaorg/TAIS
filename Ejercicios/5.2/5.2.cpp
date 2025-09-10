
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class CicloDirigido {
public:
	using Camino = deque<int>;
	CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
		apilado(g.V(), false), hayciclo(false) {
		for (int v = 0; v < g.V(); ++v)
			if (!visit[v])
				dfs(g, v);
	}
	bool hayCiclo() const { return hayciclo; }
	Camino const& ciclo() const { return _ciclo; }

private:
	std::vector<bool> visit;
	std::vector<int>  ant;
	// visit[v] = ¿se ha alcanzado a v en el dfs?
	// ant[v] = vértice anterior en el camino a v
	std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
	Camino _ciclo;
	// ciclo dirigido (vacío si no existe)
	bool hayciclo;
	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {
			if (hayciclo) // si hemos encontrado un ciclo terminamos
				return;
			if (!visit[w]) { // encontrado un nuevo vértice, seguimos
				ant[w] = v; dfs(g, w);
			}
			else if (apilado[w]) { // hemos detectado un ciclo
				// se recupera retrocediendo
				hayciclo = true;
				for (int x = v; x != w; x = ant[x])
					_ciclo.push_front(x);
				_ciclo.push_front(w); _ciclo.push_front(v);
			}
		}
		apilado[v] = false;
	}
};


class OrdenTopologico {
public:
	// g es DAG
	OrdenTopologico(Digrafo const& g) : visit(g.V(), false) {
		for (int v = 0; v < g.V(); ++v)
			if (!visit[v])
				dfs(g, v);
	}
	// devuelve la ordenación topológica
	std::deque<int> const& orden() const {
		return _orden;
	}
private:
	std::vector<bool> visit;
	std::deque<int> _orden; // ordenación topológica
	void dfs(Digrafo const& g, int v) {
		visit[v] = true;
		for (int w : g.ady(v))
			if (!visit[w])
				dfs(g, w); 
		_orden.push_front(v);
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int vert, arist;

	cin >> vert >> arist;
	if (!std::cin)  // fin de la entrada
		return false;

	Digrafo grafo(vert);
	for (int i = 0; i < arist; i++) {
		int vert1, vert2;
		cin >> vert1 >> vert2;
		grafo.ponArista(vert1 - 1, vert2 - 1);
	}
	// resolver el caso posiblemente llamando a otras funciones
	CicloDirigido ciclo(grafo);


	if (ciclo.hayCiclo()) {
		cout << "Imposible";
	}
	else {
		OrdenTopologico ordenes(grafo);

		deque<int> res = ordenes.orden();
		while (!res.empty()) {
			cout << res.front() + 1 << " ";
			res.pop_front();
		}
		// escribir la solución
	}
	cout << endl;
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
