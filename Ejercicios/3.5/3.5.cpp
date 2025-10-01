
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct Tendencia {

	int n_citas;
	int tiempo;

};

struct Comparador {
	bool operator()(Tendencia const& a, Tendencia const& b) const {
		if (a.n_citas != b.n_citas) return a.n_citas > b.n_citas; 
		return a.tiempo > b.tiempo;                 
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	// resolver el caso posiblemente llamando a otras funciones

    unordered_map<string, int> idTema;
    vector<string> temas; 
    vector<Tendencia> tendencias; 

    IndexPQ<Tendencia, Comparador> pq(N * 2, Comparador());

    long long tiempo = 0;
    int Id_siguiente = 0;

    for (int i = 0; i < N; i++) {
        string tipo;
        cin >> tipo;

        if (tipo == "C") {
            string tema;
            long long k;
            cin >> tema >> k;

            if (idTema.count(tema) == 0) {
                idTema[tema] = Id_siguiente++;
                temas.push_back(tema);
                tendencias.push_back({ 0, 0 });
            }
            int id = idTema[tema];
            tendencias[id].n_citas += k;
            tendencias[id].tiempo = ++tiempo;
            pq.update(id, tendencias[id]);

        }
        else if (tipo == "E") {
            string tema;
            long long k;
            cin >> tema >> k;

            auto it = idTema.find(tema);
            if (it != idTema.end()) { 
                int id = it->second;
                tendencias[id].n_citas -= k;
                if (tendencias[id].n_citas < 0) tendencias[id].n_citas = 0; 
                pq.update(id, tendencias[id]);
            }
        }
        else if (tipo == "TC") {
            // obtener el podio
            vector<pair<int, Tendencia>> extraidos;
            vector<string> podio;

            while (!pq.empty() && (int)podio.size() < 3) {
                auto top = pq.top();
                pq.pop();
                int id = top.elem;
                Tendencia Tendencia = top.prioridad;

                if (tendencias[id].n_citas == Tendencia.n_citas &&
                    tendencias[id].tiempo == Tendencia.tiempo &&
                    tendencias[id].n_citas > 0) {
                    podio.push_back(temas[id]);
                }
                extraidos.push_back({ id, Tendencia });
            }

            for (auto& p : extraidos) {
                int id = p.first;
                if (tendencias[id].n_citas > 0)
                    pq.update(id, tendencias[id]);
            }

            for (int j = 0; j < (int)podio.size(); j++) {
                cout << j + 1 << " " << podio[j] << "\n";
            }
        }
    }
    cout << "---\n";
    return true;
}


	// escribir la solución

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

