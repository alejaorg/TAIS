/*@ <authors>
 *

Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.*@ </authors>*/

#include <iostream>
#include <fstream>
#include <vector>
#include "ConjuntosDisjuntos.h"

using namespace std;
// propios o los de las estructuras de datos de clase

void petrolero(vector<vector<bool>>& matriz, ConjuntosDisjuntos& conj, int f, int c) {

}

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
int rellenarConjunto(ConjuntosDisjuntos& conj, const vector<bool>& matriz, int i, int j, int cols) {

    int act = i * cols + j;
    vector<pair<int, int>> dirs(8);
    dirs.at(0) = { -1, -1 };
    dirs.at(1) = { -1, 0 };
    dirs.at(2) = { -1, 1 };
    dirs.at(3) = { 0, -1 };
    dirs.at(4) = { 0, 1 };
    dirs.at(5) = { 1, -1 };
    dirs.at(6) = { 1, 0 };
    dirs.at(7) = { 1, 1 };

    for (int z = 0; z < dirs.size(); z++) {
        int aux1 = i + dirs.at(z).first;
        int aux2 = j + dirs.at(z).second;
        if (aux1 >= 0 && aux1 < matriz.size() / cols && aux2 >= 0 && aux2 < cols) {
            int pos = aux1 * cols + aux2;
            if (matriz.at(pos))
                conj.unir(act, pos);
        }

    }

    return conj.cardinal(act);
}


bool resuelveCaso() {
    // leer los datos de la entrada
    int fil, col;
    cin >> fil >> col;
    if (!std::cin)  // fin de la entrada
        return false;

    int maxMancha = 0;

    ConjuntosDisjuntos conjunto(fil * col);
    vector<bool> matriz(fil * col);
    for (int i = 0; i < fil; i++) {
        for (int j = 0; j < col; j++) {
            char a;
            cin >> a;
            matriz[i * col + j] = a == '#';
            if (matriz[i * col + j])
                maxMancha = max(rellenarConjunto(conjunto, matriz, i, j, col), maxMancha);
        }
    }

    cout << maxMancha << " ";
    int nC;
    cin >> nC;
    for (int i = 0; i < nC; i++) {
        int f, c;
        cin >> f >> c;
        f--; c--;
        matriz[f * col + c] = true;
        maxMancha = max(rellenarConjunto(conjunto, matriz, f, c, col), maxMancha);
        cout << maxMancha << " ";
    }

    // resolver el caso posiblemente llamando a otras funciones

    cout << endl;

    // escribir la solución

    return true;
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}