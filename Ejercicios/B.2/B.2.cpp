
/*@ <authors>
 *
 * Jorge Pérez Ramírez F32
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

int aibofobia(string const& word, int const& i, int const& j, vector<vector<int>>& matriz) {
	int& res = matriz[i][j];
	if (res == -1) {
		if (i >= j) res = 0;
		else if (word[i] == word[j]) 
			res = aibofobia(word, i + 1, j - 1, matriz);
		else 
			res = min(aibofobia(word, i + 1, j, matriz), aibofobia(word, i, j - 1, matriz)) + 1;
		
	}
	return res;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	string word;
	cin >> word;
	if (!std::cin)  // fin de la entrada
		return false;

	int wordSize = word.length();
	
	
	vector<vector<int>> matriz(wordSize, vector<int>(wordSize, -1));
	

	int sol = aibofobia(word, 0, wordSize - 1, matriz);
	// resolver el caso posiblemente llamando a otras funciones
	
	int tam = wordSize + sol;
	vector<char> solWord(tam);

	// escribir la solución
	cout << sol << " ";

	int i = 0, j = wordSize - 1;
	int l1 = 0, l2 = j + sol;
	while (i <= j) {
		if (i == j) {
			solWord[l1] = word[i];
			solWord[l2] = word[i];
			i++;
			j--;
		}
		else if (sol > 0 && matriz[i + 1][j] == sol - 1) {
			solWord[l1] = word[i];
			solWord[l2] = word[i];
			sol--; i++;
		}
		else if (sol > 0 && matriz[i][j - 1] == sol - 1) {
			solWord[l1] = word[j];
			solWord[l2] = word[j];
			sol--; j--;
		}
		else {
			solWord[l1] = word[i];
			solWord[l2] = word[i];
			i++;
			j--;
		}
		l1++;
		l2--;
	}
	for (char i : solWord)
		cout << i;
	cout << "\n";

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
