#include <iostream>
#include <cmath> 
#include "Solucionador.hpp"

using namespace std;

bool esEstadoValido(int m, int c) {
    if (m < 0 || m > 3 || c < 0 || c > 3) return false;
    if (m > 0 && m < c) return false; // Regla Izq
    int mDer = 3 - m;
    int cDer = 3 - c;
    if (mDer > 0 && mDer < cDer) return false; // Regla Der
    return true;
}

Solucionador::Solucionador() {

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<2; k++)
                visitados[i][j][k] = false;

    int mM[] = {1, 2, 0, 0, 1};
    int mC[] = {0, 0, 1, 2, 1};
    
    for(int i=0; i<5; i++) {
        movM[i] = mM[i];
        movC[i] = mC[i];
    }
}

bool Solucionador::fueVisitado(int m, int c, int b) {
    return visitados[m][c][b];
}

void Solucionador::marcarVisitado(int m, int c, int b) {
    visitados[m][c][b] = true;
}

void Solucionador::resolver() {
    Cola* cola = new Cola();
    
    Nodo* raiz = new Nodo(3, 3, 1, nullptr, 0);
    cola->encolar(raiz);
    marcarVisitado(3, 3, 1);

    Nodo* meta = nullptr;

    // --- BFS ---
    while (!cola->estaVacia()) {
        Nodo* actual = cola->desencolar();

        if (actual->datos->m == 0 && actual->datos->c == 0 && actual->datos->b == 0) {
            meta = actual;
            break; 
        }

        for (int i = 0; i < 5; i++) {
            int nm, nc, nb;

            if (actual->datos->b == 1) { 
                nm = actual->datos->m - movM[i];
                nc = actual->datos->c - movC[i];
                nb = 0;
            } else { 
                nm = actual->datos->m + movM[i];
                nc = actual->datos->c + movC[i];
                nb = 1;
            }

            if (esEstadoValido(nm, nc) && !fueVisitado(nm, nc, nb)) {
                Nodo* hijo = new Nodo(nm, nc, nb, actual, actual->paso + 1);
                cola->encolar(hijo);
                marcarVisitado(nm, nc, nb);
            }
        }
    }

    if (meta != nullptr) {
        cout << "=== SOLUCION POO + ARCHIVOS ===" << endl;
        imprimirCaminoRecursivo(meta);
        cout << "-------------------------------" << endl;
    } else {
        cout << "No hay solucion." << endl;
    }
    
    delete cola;
}

void Solucionador::imprimirCaminoRecursivo(Nodo* n) {
    if (n == nullptr) return;

    imprimirCaminoRecursivo(n->padre);

    if (n->padre != nullptr) {
        int dm = abs(n->padre->datos->m - n->datos->m);
        int dc = abs(n->padre->datos->c - n->datos->c);
        
        cout << "Paso " << n->paso << ": ";
        if (n->padre->datos->b == 1) cout << "IDA (->)    ";
        else                         cout << "VUELTA (<-) ";
        
        cout << "| Bote: " << dm << "M " << dc << "C | ";
        cout << "Izq: " << n->datos->m << "M " << n->datos->c << "C" << endl;
    } else {
        cout << "INICIO: Izq(3M, 3C) - Der(0M, 0C)" << endl;
    }
}