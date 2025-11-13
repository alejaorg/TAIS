
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 * Alejandro Orgaz Fernandez F29
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <stack>

using namespace std;
  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
const int CENTINELA = 0;

struct Horario {
	int dia;
	int hora;
	int min;
	int duracion;

	bool operator<(const Horario& h2) const {
		if (this->dia == h2.dia) {
			if (this->hora == h2.hora) {
				return this->min <= h2.min;
			}
			return this->hora <= h2.hora;
		}
		return this->dia <= h2.dia;
	}

	Horario getFinal() {
		int auxdia = this->duracion / (24 * 60);
		int auxhora = this->duracion % (24 * 60);
		int minaux = this->min + auxhora % 60;
		int horaux = this->hora;
		if (minaux >= 60) { 
			horaux++;
			minaux -= 60;
		} 
		int diaaux = this->dia;
		horaux += auxhora / 60;
		if (horaux >= 24) {
			diaaux++;
			horaux -= 24;
		}
		diaaux += auxdia;
 		return {diaaux, horaux, minaux, duracion};
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;	
	if (N == CENTINELA)
		return false;

	priority_queue<Horario, vector<Horario>, less<Horario>> q;

	for (int i = 0; i < N; i++) {
		int dia, hora, min, duracion;
		int auxint;
		string aux;
		cin >> auxint >> aux;
		cin >> duracion;
		hora = stoi(aux.substr(0, 2));
		min = stoi(aux.substr(3, 5));
		q.push({ auxint, hora, min, duracion + 10});
	}
	// resolver el caso posiblemente llamando a otras funciones
	stack<Horario> res;
	res.push(q.top());
	q.pop();
	while (!q.empty()) {
		Horario aux = q.top();
		if (aux.getFinal() < res.top()) {
			res.push(aux);
		}
		q.pop();
	}

	// escribir la solución
	cout << res.size() << "\n";

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
