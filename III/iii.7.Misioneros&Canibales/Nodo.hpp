#ifndef NODO_HPP
#define NODO_HPP

#include "Estado.hpp"

struct Nodo {
    Estado* datos;    // Puntero a datos dinámicos
    Nodo* siguiente;  // Para la estructura de Cola
    Nodo* padre;      // Para el Backtracking (historial)
    int paso;         // Número de paso actual

    // Constructor del Nodo
    Nodo(int m, int c, int b, Nodo* p, int nPaso) {
        datos = new Estado; // Memoria dinámica
        datos->m = m;
        datos->c = c;
        datos->b = b;
        padre = p;
        siguiente = nullptr;
        paso = nPaso;
    }

    // Destructor para limpiar el estado interno
    ~Nodo() {
        if (datos) delete datos;
    }
};

#endif