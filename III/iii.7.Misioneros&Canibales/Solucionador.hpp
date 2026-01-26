#ifndef SOLUCIONADOR_HPP
#define SOLUCIONADOR_HPP

#include "Cola.hpp"
#include "Estado.hpp"

class Solucionador {
private:

    bool visitados[4][4][2];
    
    int movM[5];
    int movC[5];

    bool fueVisitado(int m, int c, int b);
    void marcarVisitado(int m, int c, int b);
    void imprimirCaminoRecursivo(Nodo* n);

public:
    Solucionador(); // Constructor
    void resolver(); // Método principal
};

#endif