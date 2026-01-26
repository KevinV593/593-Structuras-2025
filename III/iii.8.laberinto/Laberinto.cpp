#include <iostream>
#include "Laberinto.hpp"

using namespace std;

Laberinto::Laberinto(int f, int c) {
    filas = f;
    cols = c;
    camino = new Pila();

    tablero = new int*[filas];
    for(int i = 0; i < filas; i++) {
        tablero[i] = new int[cols];
    }

    visitados = new bool*[filas];
    for(int i = 0; i < filas; i++) {
        visitados[i] = new bool[cols];
        // Inicializar en false
        for(int j=0; j < cols; j++) visitados[i][j] = false;
    }
}

Laberinto::~Laberinto() {

    for(int i = 0; i < filas; i++) {
        delete[] tablero[i];
        delete[] visitados[i];
    }

    delete[] tablero;
    delete[] visitados;
    delete camino;
}

void Laberinto::configurarTablero() {
    // 0 = Pasillo, 1 = Pared
    int mapa[5][5] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    for(int i=0; i<filas; i++) {
        for(int j=0; j<cols; j++) {
            tablero[i][j] = mapa[i][j];
        }
    }

    inicio = {0, 0}; // Esquina superior izq
    fin = {4, 4};    // Esquina inferior der
}

// --- ALGORITMO CORE: BACKTRACKING CON PILA ---
bool Laberinto::resolver() {
    // 1. Meter el inicio en la pila
    camino->push(inicio.fila, inicio.col);
    visitados[inicio.fila][inicio.col] = true;

    // Movimientos posibles: Arriba, Derecha, Abajo, Izquierda
    // Arrays paralelos para iterar direcciones fácilmente
    int dFil[] = {-1, 0, 1, 0};
    int dCol[] = {0, 1, 0, -1};

    while (!camino->estaVacia()) {
        Coordenada actual = camino->peek();

        // CASO BASE: Llegamos a la meta?
        if (actual == fin) {
            return true; // Éxito, la pila tiene el camino completo
        }

        bool seMovio = false;

        // Intentar moverse a un vecino
        for (int i = 0; i < 4; i++) {
            int sigF = actual.fila + dFil[i];
            int sigC = actual.col + dCol[i];

            // Validaciones:
            // 1. Dentro de limites
            // 2. No es pared (tablero != 1)
            // 3. No ha sido visitado aun
            if (sigF >= 0 && sigF < filas && sigC >= 0 && sigC < cols &&
                tablero[sigF][sigC] != 1 && 
                !visitados[sigF][sigC]) {
                
                // AVANZAR
                camino->push(sigF, sigC);
                visitados[sigF][sigC] = true;
                seMovio = true;
                break; // Importante: Solo damos UN paso y reiniciamos el bucle while
            }
        }

        // Si revisamos los 4 lados y no pudimos movernos (Callejón sin salida)
        if (!seMovio) {
            // RETROCEDER (Backtracking)
            camino->pop();
        }
    }

    return false; // Pila vacía y no encontramos meta
}

void Laberinto::imprimir() {
    cout << "--- MAPA DEL LABERINTO ---" << endl;
    cout << "S: Inicio, E: Fin, #: Pared, .: Camino" << endl;
    
    // Para imprimir la solución, usaremos 'camino->contiene()'
    // Esto es ineficiente O(N^2) pero visualmente claro para consola pequeña
    
    for(int i=0; i<filas; i++) {
        for(int j=0; j<cols; j++) {
            if (i == inicio.fila && j == inicio.col) cout << "S ";
            else if (i == fin.fila && j == fin.col)  cout << "E ";
            else if (tablero[i][j] == 1)             cout << "# ";
            else if (camino->contiene(i, j))         cout << ". "; // Parte de la solución
            else                                     cout << "  "; // Pasillo vacío
        }
        cout << endl;
    }
    cout << "--------------------------" << endl;
    
    if (!camino->estaVacia()) {
        camino->mostrarCamino();
    } else {
        cout << "No se pudo resolver." << endl;
    }
}