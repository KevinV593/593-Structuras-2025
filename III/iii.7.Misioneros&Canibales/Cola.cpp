#include "Cola.hpp"

Cola::Cola() {
    frente = nullptr;
    final = nullptr;
}

Cola::~Cola() {
    // Limpieza básica si queda algo al destruir la cola
    while (!estaVacia()) {
        Nodo* temp = desencolar();
        // Nota: En un caso real, aquí decidiríamos si borrar 'temp'
        // o si pertenece a otro ámbito.
    }
}

bool Cola::estaVacia() {
    return frente == nullptr;
}

void Cola::encolar(Nodo* n) {
    n->siguiente = nullptr; 
    
    if (estaVacia()) {
        frente = n;
        final = n;
    } else {
        final->siguiente = n;
        final = n;
    }
}

Nodo* Cola::desencolar() {
    if (estaVacia()) return nullptr;
    
    Nodo* temp = frente;
    frente = frente->siguiente;
    
    if (frente == nullptr) {
        final = nullptr;
    }
    return temp;
}