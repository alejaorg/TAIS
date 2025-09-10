#include <iostream>
#include <fstream>
#include <vector>
#include <queue> // para priority_queue
using namespace std;

bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0) return false;

	priority_queue<int, vector<int>, greater<int>> heap;

	for (int i = 0; i < n; ++i) {
		int seguidores;
		cin >> seguidores;
		heap.push(seguidores);
	}

	long long total = 0;

	while (heap.size() > 1) {
		int a = heap.top(); heap.pop();
		int b = heap.top(); heap.pop();
		int nuevo = a + b;
		total += nuevo;
		heap.push(nuevo);
	}

	cout << total << '\n';
	return true;
}

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
