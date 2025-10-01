
    /*@ <authors>
     *
     * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
     * F29 Alejandro Orgaz Fernández
     *
     *@ </authors> */

    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <algorithm>
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
    struct Event {
	    int tiempo;
	    int tipo; // +1 = inicio, -1 = fin
        int periodo = 0;
	    bool operator>(const Event& otro) const {
		    if (tiempo == otro.tiempo) return tipo > otro.tipo;
		    return tiempo > otro.tiempo;
	    }
    };


    bool resuelveCaso() {
	    // leer los datos de la entrada
	    int N, M, T;

	    cin >> N >> M >> T;
	    if (!std::cin)  // fin de la entrada
		    return false;

	    // resolver el caso posiblemente llamando a otras funciones
            priority_queue<Event, vector<Event>, greater<Event>> pq;

            // Tareas únicas
            for (int i = 0; i < N; i++) {
                int c, f;
                cin >> c >> f;
                if (c < T) {
                    pq.push({ c, +1 });
                    pq.push({ min(f, T), -1 });
                }
            }

            // Tareas periódicas
            for (int i = 0; i < M; i++) {
                int c, f, p;
                cin >> c >> f >> p;
                pq.push({ c, +1, p});
                pq.push({ min(f, T), -1, p});
            }

            int activo = 0;
            bool conflicto = false;
            while (!pq.empty()) {
                Event e = pq.top();
                pq.pop();
                activo += e.tipo;
                if (e.periodo != 0 && e.tiempo + e.periodo < T) {
                    pq.push({ e.tiempo + e.periodo, e.tipo, e.periodo });
                }
                if (activo > 1) {
                    conflicto = true;
                    break;
                }
            }

            cout << (conflicto ? "SI" : "NO") << "\n";
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

